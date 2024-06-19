#include "bbgl.h"

constexpr int kTimerID = 101;


BBGL::BBGL(int width, int height) {
    this->width = width;
    this->height = height;
    this->buffs = new graphic_buffers(width,height);

    for (int x=0;x<width;x++) {
        for (int y=0;y<height;y++) {
            this->buffs->set_pixel(x,y,RGB(0,0,0));
        }
    }

    this->buffs->swap();

    for (int x=0;x<width;x++) {
        for (int y=0;y<height;y++) {
            this->buffs->set_pixel(x,y,RGB(0,0,0));
        }
    }

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
        "buffered window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, this->width, this->height, 0, 0, hInstance, this))
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
                this->buffs->clear();
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
        case WM_GETMINMAXINFO: {
                MINMAXINFO *minmax = (MINMAXINFO *)lParam;
                minmax->ptMaxTrackSize.x = minmax->ptMinTrackSize.x = this->width;
                minmax->ptMaxTrackSize.y = minmax->ptMinTrackSize.y = this->height;
                break;
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