#pragma once
#ifndef _BBGL_H_
#define _BBGL_H_

#include <windows.h>
#include <stdint.h>
#include <utility>
#include <algorithm>
#include <map>
#include "graphic_buffers.h"

/**
 * The struct used by BBGL to store its options related to window size and resize
*/
struct BBGLWINDOWOPTION {
    /**
     * Allows the window to be resized or not. if true, bbgl will use minWidth and minHeight to determine the minimum
     * size the window can be as well as maxWidth and maxHeight to determine the maximum size.
    */
    bool allowResize = false;
    /**
     * Allows the window to be maximised. Overrides allowResize. Will ignore maxWidth and maxHeight but will still use
     * minWidth and minHeight to determine the minimum window size
    */
    bool allowMaximised = false;
    /**
     * The minimum width in pixel the window can be
    */
    int minWidth = 512;
    /**
     * The height width in pixel the window can be
    */
    int minHeight = 512;
    /**
     * The maximum width in pixel the window can be
    */
    int maxWidth = 512;
    /**
     * The maximum height in pixel the window can be
    */
    int maxHeight = 512;
};

/**
 * The struct used by BBGL to store its options related to buffers
*/
struct BBGLBUFFEROPTION {
    /**
     * Determine if the buffer should be cleared every frame. if false pixels that where not overwriten will keep their
     * color from the last frame
    */
    bool clearBufferOnDraw = true;
    /**
     * Determine the color used to clear the buffer with
    */
    COLORREF baseColor = RGB(0,0,0);
};

/**
 * The struct used by BBGL to store its options
*/
struct BBGLOPTIONS {
    /**
     * Determine the name of the window that will be opened by BBGL
    */
    char* windowName = "BBGL window";
    /**
     * The structure containing the options related to window size and resize options
    */
    BBGLWINDOWOPTION windowOptions;
    /**
     * The structure containing the options related to the window buffer
    */
    BBGLBUFFEROPTION bufferOptions;
};

/**
 * A struct containing the diffrent input information of the mouse
*/
struct BBGLMOUSEINPUTS {
    /**
     * true if the left click is held down
    */
    bool leftClick = false;

    /**
     * true if the right click is held down
    */
    bool rightClick = false;

    /**
     * true if the middle click is held down
    */
    bool middleClick = false;

    /**
     * the current X position of the mouse
    */
    int positionX = 0;

    /**
     * the current X position of the mouse
    */
    int positionY = 0;
};

/**
 * A struct containing the different inputs received by the window
*/
struct BBGLINPUTS {
    /**
     * A struct containing the diffrent input information of the mouse
    */
    BBGLMOUSEINPUTS mouse;

    /**
     * A vector containing the keys that are currently held
    */
    std::map<int,bool> keyDown;
};

/**
 * The main class of BBGL instanciate it, fill the draw and update functions
 * then call the start function to create the window
*/
class BBGL {
private:
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static LRESULT CALLBACK wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK _wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    PAINTSTRUCT ps;
    HDC hdc;
    HDC hdc_bmp;
    HGDIOBJ old_bmp;
public:
    /**
     * With no arguments given bbgl will create a black 512x512 non resizeable window
    */
    BBGL();

    /**
     * Fills the options variable with the given BBGLOPTIONS object before making the window
    */
    BBGL(BBGLOPTIONS bbglOptions);
    ~BBGL();

    /**
     * The variable used for keeping the options for BBGL
    */
    BBGLOPTIONS options;

    /**
     * The function called before drawing to on the window
     * use this function to update the rest of your program ex: advance 1 tick through a simulation
    */
    void (*update)();

    /**
     * Call this function after having setup your options in the options variable
    */
    void start();

    /**
     * The buffer that will be used to draw on the screen
    */
    graphic_buffers *buffs;

    /**
     * The variable containing the user inputs
    */
    BBGLINPUTS inputs;
};

#endif
