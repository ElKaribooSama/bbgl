#include "graphic_buffers.h"

graphic_buffers::graphic_buffers(int wd, int hgt, COLORREF color) : 
                 wd_(wd),
                 hgt_(hgt),
                 bc_(color) {

    HDC hdcScreen = GetDC(NULL);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = wd;
    bmi.bmiHeader.biHeight = -hgt; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    buffer.hbm = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&buffer.data), NULL, 0);
    ReleaseDC(NULL, hdcScreen);

    clear();
}

HBITMAP graphic_buffers::bmp() {
    return buffer.hbm;
}

size_t graphic_buffers::size() {
    return static_cast<size_t>(wd_ * hgt_);
}

int graphic_buffers::width() {
    return wd_;
}

int graphic_buffers::height() {
    return hgt_;
}

void graphic_buffers::clear() {
    std::fill(buffer.data, buffer.data + size(), bc_);
}

void graphic_buffers::safe_set_pixel(int x, int y, uint32_t pix) {
    if (x > wd_ || x < 0 || y > hgt_ || y < 0) return;
    buffer.data[y * wd_ + x] = pix;
}

void graphic_buffers::set_pixel(int x, int y, uint32_t pix) {
    buffer.data[y * wd_ + x] = pix;
}

graphic_buffers::~graphic_buffers() {
    DeleteObject(buffer.hbm);
}
