#pragma once
#ifndef _GRAPHICBUFFER_H_
#define _GRAPHICBUFFER_H_

#include <windows.h>
#include <stdint.h>
#include <utility>
#include <algorithm>

struct BBGLGRAPHICBUFFER {
    HBITMAP hbm;
    uint32_t* data;
};

class graphic_buffers {
    BBGLGRAPHICBUFFER buffer;
    int wd_;
    int hgt_;
    COLORREF bc_;

public:
    graphic_buffers(int wd, int hgt, COLORREF color);
    HBITMAP bmp();
    size_t size();
    int width();
    int height();
    void clear();
    void safe_set_pixel(int x, int y, uint32_t pix);
    void set_pixel(int x, int y, uint32_t pix);
    ~graphic_buffers();
};

#endif
