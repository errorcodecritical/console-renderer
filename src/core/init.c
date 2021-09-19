#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

#include "event.h"
#include "render.h"
#include "camera.h"

#include "luacore.h"

#include "helper.h"

// TODO: Thread supervisor to check for stalled threads;

char is_running = 0x1;

int main() {
    pthread_t context[10];
    pthread_create(&context[0], NULL, event.init, NULL);

    pthread_create(&context[1], NULL, lua.runfile, "src/scripts/test1.lua");

    // Perform render setup
    viewport.init();
    
    // Perform control setup

    // Main game loop
    msleep(999);

    while (is_running) {
        double render_delta = (double)(clock() - viewport.clock) / CLOCKS_PER_SEC;

        if (render_delta > (1.0 / 60.0)) {
            viewport.update(render_delta, camera.update);
            msleep(10);
        }
    };

    return 0;
}