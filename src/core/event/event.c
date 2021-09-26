#include "event.h"

static void* __Init(void* args) {
    while (1) {
        for (int i = 0; i < registry_size; i++) {
            if (registry[i].state == 1) {
                for (int n = 0; n < registry[i].num_listeners; n++) {
                    pthread_t id;
                    pthread_create(&id, NULL, registry[i].listeners[n], args);
                }
                registry[i].state = 0;
            }
            msleep(1);
        }
    }
}

static void __Connect(char* name, void* listener) {
    printf("CONNECTED: %s\n", name);
    for (int i = 0; i < registry_size; i++) {
        if (!strcmp(name, registry[i].name)) { 
            registry[i].num_listeners += 1;
            registry[i].listeners = realloc(
                registry[i].listeners, 
                registry[i].num_listeners * sizeof(void*)
            );
            registry[i].listeners[registry[i].num_listeners - 1] = listener;
        }
    }
}

static void __Disconnect(char* name, void* listener) {
    for (int i = 0; i < registry_size; i++) {
        if (!strcmp(name, registry[i].name)) { 
            registry[i].num_listeners -= 1;
        }
    }
}

static void __Create(char* name) {
    printf("REGISTERED: %s\n", name);
    registry[registry_size] = (struct __Signal) {
        .name = name,
        .state = 0,
        .num_listeners = 0,
        .listeners = NULL
    };
    registry_size += 1;
}

static void __Fire(char* name, void* args) {
    printf("FIRED: %s\n", name);
    for (int i = 0; i < registry_size; i++) {
        if (!strcmp(name, registry[i].name)) {
            registry[i].state = 1;
        }
        msleep(10);
    }
}

struct __EventMethods event = {
    .init = __Init,
    .create = __Create,
    .connect = __Connect,
    .disconnect = __Disconnect,
    .fire = __Fire
};