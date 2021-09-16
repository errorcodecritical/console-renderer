// Defines
#define __USE_POSIX199309

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "render.h"
#include "camera.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

char is_running = 0x1;

int main() {
    // Perform render setup
    viewport.Init();
    
    // Perform control setup

    // Main game loop

    while (is_running) {
        double render_delta = (double)(clock() - viewport.clock) / CLOCKS_PER_SEC;

        if (render_delta > (1.0 / 60.0)) {
            viewport.Update(render_delta, camera.update);
        }
    };

    return 0;
}