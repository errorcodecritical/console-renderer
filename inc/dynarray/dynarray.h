#ifndef __DYNARRAY_H
#define __DYNARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define assert(condition, error) if (!condition) {printf(error); return;} // static assertion

typedef struct __SetObject {
    int width;
    int length;
    int next;
    void* contents;
} set_t;

extern struct __SetMethods {
    set_t* (*create)(int width, int length);
    void (*destroy)(set_t** set_ptr);
    void (*insert)(set_t** set_ptr, int index, void* value);
    void (*remove)(set_t** set_ptr, int index);
} set;

#endif