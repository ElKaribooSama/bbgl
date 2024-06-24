#include "bbgl.h"

constexpr int kTimerID = 101;


BBGL::BBGL() {
    BBGLOPTIONS baseoptions;
    this->options = baseoptions;
    this->buffs = new graphic_buffers(baseoptions.windowOptions.minWidth,
                                      baseoptions.windowOptions.minHeight,
                                      baseoptions.bufferOptions.baseColor);
}

BBGL::BBGL(BBGLOPTIONS bbglOptions) {
    this->options = bbglOptions;
    this->buffs = new graphic_buffers(bbglOptions.windowOptions.minWidth,
                                      bbglOptions.windowOptions.minHeight,
                                      bbglOptions.bufferOptions.baseColor);
}

BBGL::~BBGL() {
    free(this->buffs);
}

void BBGL::start() {
    this->WinMain(GetModuleHandle(NULL),NULL,0,0);
}

int WINAPI BBGL::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG msg = { 0 };
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = wndproc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = "swap_buffers_window";
    if (!RegisterClass(&wc))
        return 1;

    if (!CreateWindow(wc.lpszClassName,
        this->options.windowName,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, this->options.windowOptions.minWidth, this->options.windowOptions.minHeight, 0, 0, hInstance, this))
        return 2;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK BBGL::wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_CREATE) {
        CREATESTRUCT *createstruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createstruct->lpCreateParams));
        SetTimer(hWnd, kTimerID, 1, NULL);
    }

    BBGL* me = reinterpret_cast<BBGL*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (me) return me->_wndproc(hWnd, message, wParam, lParam);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK BBGL::_wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_TIMER: {
                this->update();
                this->draw();
                this->buffs->swap();

                //if you know that you will never need to clear the buffer you can comment the if
                //if you always want to clear you can remove the if itself and keep the clear
                if (this->options.bufferOptions.clearBufferOnDraw) {
                    this->buffs->clear();
                }
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
        case WM_GETMINMAXINFO: {
                MINMAXINFO *minmax = (MINMAXINFO *)lParam;
                minmax->ptMinTrackSize.x = this->options.windowOptions.minWidth;
                minmax->ptMinTrackSize.y = this->options.windowOptions.minHeight;

                if (!this->options.windowOptions.allowResize) {
                    minmax->ptMaxTrackSize.x = minmax->ptMinTrackSize.x;
                    minmax->ptMaxTrackSize.y = minmax->ptMinTrackSize.y;
                    break;
                }
                
                if (!this->options.windowOptions.allowMaximised) {
                    minmax->ptMaxTrackSize.x = this->options.windowOptions.maxWidth;
                    minmax->ptMaxTrackSize.y = this->options.windowOptions.maxHeight;
                    break;
                }


                break;
            }
        case WM_SIZE: {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                this->buffs = new graphic_buffers(width,
                                                  height,
                                                  this->options.bufferOptions.baseColor);
            }
        case WM_PAINT: {
                hdc = BeginPaint(hWnd, &ps);
                hdc_bmp = CreateCompatibleDC(hdc);
                old_bmp = SelectObject(hdc_bmp, buffs->front_bmp());

                BitBlt(hdc, 0, 0, this->buffs->width(), this->buffs->height(), hdc_bmp, 0, 0, SRCCOPY);

                SelectObject(hdc, old_bmp);
                DeleteDC(hdc_bmp);
                EndPaint(hWnd, &ps);
            }
            break;

        case WM_DESTROY: {
                delete this->buffs;
            }
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    return 0;
}