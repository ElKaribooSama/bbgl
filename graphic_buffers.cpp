#include "graphic_buffers.h"

graphic_buffers::graphic_buffers(int wd, int hgt) : 
                 wd_(wd),
                 hgt_(hgt),
                 front_(create_graphics_buffer(wd, hgt)),
                 back_(create_graphics_buffer(wd, hgt)) {
    clear();
}

graphics_buffer graphic_buffers::create_graphics_buffer(int wd, int hgt) {
    HDC hdcScreen = GetDC(NULL);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = wd;
    bmi.bmiHeader.biHeight = -hgt; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    graphics_buffer gb;
    gb.hbm = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&gb.data), NULL, 0);

    ReleaseDC(NULL, hdcScreen);
    return gb;
}

HBITMAP graphic_buffers::front_bmp() {
    return front_.hbm;
}

void graphic_buffers::swap() {
    std::swap(front_, back_);
}

size_t graphic_buffers::size() const {
    return static_cast<size_t>(wd_ * hgt_);
}

int graphic_buffers::width() const {
    return wd_;
}

int graphic_buffers::height() const {
    return hgt_;
}

void graphic_buffers::clear() {
    std::fill(back_.data, back_.data + size(), 0);
}

void graphic_buffers::set_pixel(int x, int y, uint32_t pix) {
    back_.data[y * wd_ + x] = pix;
}

graphic_buffers::~graphic_buffers() {
    DeleteObject(front_.hbm);
    DeleteObject(back_.hbm);
}
