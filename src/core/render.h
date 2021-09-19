#ifndef __RENDER_H
#define __RENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

extern struct __Viewport {
    void (*init)();
    void (*update)(double delta, void (*update_function)(double delta));

    clock_t clock;
    struct {
        unsigned short int y;
        unsigned short int x;
        unsigned short int px;
        unsigned short int py;
    } viewport_size;
    wchar_t* viewport_buffer;
} viewport;

#endif