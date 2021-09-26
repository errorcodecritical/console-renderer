#include <stdio.h>
#include "helper.h"

void msleep(int millisec) {
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = millisec * 1000000L;
    nanosleep(&req, (struct timespec*)NULL);
}