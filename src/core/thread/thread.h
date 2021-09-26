#ifndef __THREAD_H
#define __THREAD_H

#include <pthread.h>

typedef struct __ThreadObject {
    int id;
    long int handle;
} thread_t;

extern struct __ThreadMethods {
    thread_t (*create)(void* routine, void* args);
} thread;

#endif