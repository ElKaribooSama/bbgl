#include <windows.h>
#include <stdint.h>
#include <utility>
#include <algorithm>
#include "graphic_buffers.h"



class BBGL
{
private:
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static LRESULT CALLBACK wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK _wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    /* data */
public:
    BBGL(int width, int height);
    ~BBGL();
    int width;
    int height;
    void (*draw)();
    void (*update)();
    void start();
    graphic_buffers *buffs;
    PAINTSTRUCT ps;
    HDC hdc;
    HDC hdc_bmp;
    HGDIOBJ old_bmp;
};


