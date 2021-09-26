#ifndef __EVENT_H
#define __EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "helper/helper.h"

static int registry_size = 0;

static struct __Signal {
    char* name;
    char state;
    int num_listeners;
    void* (**listeners)(void* args);
} registry[256];

extern struct __EventMethods {
    void* (*init)();
    void (*create)(char* name);
    void (*fire)(char* name, void* args);
    void (*connect)(char* name, void* listener);
    void (*disconnect)(char* name, void* listener);
} event;

#endif