#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <stdint.h>

void draw_line(char* framebuffer, int width, int height, int bpp,
               int x0, int y0, int x1, int y1, uint32_t color);
void clear_framebuffer(char* framebuffer, int width, int height, int bpp, uint32_t color);

#endif