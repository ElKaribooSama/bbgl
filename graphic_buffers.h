#include <windows.h>
#include <stdint.h>
#include <utility>
#include <algorithm>

struct graphics_buffer {
    HBITMAP hbm;
    uint32_t* data;
};

class graphic_buffers {
    graphics_buffer front_;
    graphics_buffer back_;
    int wd_; 
    int hgt_;
    COLORREF bc_;

public:

    graphic_buffers(int wd, int hgt, COLORREF color);
    graphics_buffer create_graphics_buffer(int wd, int hgt);
    HBITMAP front_bmp();
    void swap();
    size_t size() const;
    int width() const;
    int height() const;
    void clear();
    void safe_set_pixel(int x, int y, uint32_t pix);
    void set_pixel(int x, int y, uint32_t pix);
    ~graphic_buffers();
};
