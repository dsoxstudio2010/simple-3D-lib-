#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#include <X11/Xlib.h>

typedef struct {
    Display* display;
    Window window;
    GC gc;
    int width;
    int height;
} X11Window;

X11Window* x11_window_create(int width, int height, const char* title);
void x11_window_destroy(X11Window* win);
void x11_window_clear(X11Window* win);
void x11_window_draw_pixel(X11Window* win, int x, int y, unsigned long color);
void x11_window_draw_line(X11Window* win, int x1, int y1, int x2, int y2, unsigned long color);
void x11_window_update(X11Window* win);
int x11_window_handle_events(X11Window* win);

#endif