#include <windows.h>
#include <stdint.h>
#include <utility>
#include <algorithm>
#include "graphic_buffers.h"

struct BBGLWINDOWOPTION {
    bool allowResize = false;
    bool allowMaximised = false;
    int minWidth = 512;
    int minHeight = 512;
    int maxWidth = 512;
    int maxHeight = 512;
};

struct BBGLBUFFEROPTION {
    bool clearBufferOnDraw = true;
    COLORREF baseColor = RGB(0,0,0);
};

struct BBGLOPTIONS {
    char* windowName = "BBGL window";
    BBGLWINDOWOPTION windowOptions;
    BBGLBUFFEROPTION bufferOptions;
};


class BBGL {
private:
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static LRESULT CALLBACK wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK _wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    /* data */
public:
    BBGL(BBGLOPTIONS bbglOptions);
    ~BBGL();
    BBGLOPTIONS options;
    void (*draw)();
    void (*update)();
    void start();
    graphic_buffers *buffs;
    PAINTSTRUCT ps;
    HDC hdc;
    HDC hdc_bmp;
    HGDIOBJ old_bmp;
};


