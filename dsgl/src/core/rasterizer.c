#include "../include/core/rasterizer.h"
#include <math.h>

void draw_line(char* framebuffer, int width, int height, int bpp,
               int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height) {
            int offset = (y0 * width + x0) * (bpp / 8);
            *((uint32_t*)(framebuffer + offset)) = color;
        }
        
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void clear_framebuffer(char* framebuffer, int width, int height, int bpp, uint32_t color) {
    int total_pixels = width * height;
    int bytes_per_pixel = bpp / 8;
    
    for (int i = 0; i < total_pixels; i++) {
        int offset = i * bytes_per_pixel;
        *((uint32_t*)(framebuffer + offset)) = color;
    }
}