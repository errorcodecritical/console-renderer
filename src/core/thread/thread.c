#include "thread.h"

// Made wrapper in case I get around to making this compatible for windows?

static thread_t __Create(void* routine, void* args) {
    thread_t new_thread = {0, 0};
    pthread_create((pthread_t*)&new_thread.id, NULL, routine, args);
    return new_thread;
}

struct __ThreadMethods thread = {
    .create = __Create
};