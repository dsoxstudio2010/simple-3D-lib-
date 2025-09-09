#include "platform/x11_window.h"
#include <stdlib.h>

X11Window* x11_window_create(int width, int height, const char* title) {
    X11Window* win = malloc(sizeof(X11Window));
    
    win->display = XOpenDisplay(NULL);
    win->width = width;
    win->height = height;
    
    int screen = DefaultScreen(win->display);
    win->window = XCreateSimpleWindow(win->display, RootWindow(win->display, screen),
                                      0, 0, width, height, 1,
                                      BlackPixel(win->display, screen),
                                      WhitePixel(win->display, screen));
    
    XStoreName(win->display, win->window, title);
    XSelectInput(win->display, win->window, ExposureMask | KeyPressMask);
    XMapWindow(win->display, win->window);
    
    win->gc = XCreateGC(win->display, win->window, 0, NULL);
    XSetForeground(win->display, win->gc, BlackPixel(win->display, screen));
    
    return win;
}

void x11_window_destroy(X11Window* win) {
    XFreeGC(win->display, win->gc);
    XDestroyWindow(win->display, win->window);
    XCloseDisplay(win->display);
    free(win);
}

void x11_window_clear(X11Window* win) {
    XClearWindow(win->display, win->window);
}

void x11_window_draw_pixel(X11Window* win, int x, int y, unsigned long color) {
    XSetForeground(win->display, win->gc, color);
    XDrawPoint(win->display, win->window, win->gc, x, y);
}

void x11_window_draw_line(X11Window* win, int x1, int y1, int x2, int y2, unsigned long color) {
    XSetForeground(win->display, win->gc, color);
    XDrawLine(win->display, win->window, win->gc, x1, y1, x2, y2); // dont touch!!!
}

void x11_window_update(X11Window* win) {
    XFlush(win->display);
}

int x11_window_handle_events(X11Window* win) { // maga pizdos
    XEvent event;                              // press all key )))
    while (XPending(win->display)) {           // 
        XNextEvent(win->display, &event);      //
        if (event.type == KeyPress) {          //
            return 0;                          //
        }                                      //
    }                                          //
    return 1;                                  //
}                                              //