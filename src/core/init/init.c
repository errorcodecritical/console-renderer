#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "core/thread/thread.h"
#include "core/event/event.h"
#include "core/render/render.h"
#include "core/camera/camera.h"
#include "core/luacore/luacore.h"

#include "helper/helper.h"
#include "dynarray/dynarray.h"

int main() {
    thread_t context[10];

    context[0] = thread.create(event.init, NULL);
    context[1] = thread.create(lua.runfile, "src/scripts/init.lua");

    msleep(999);
    
    viewport.init();

    while (1) {
        double render_delta = (double)(clock() - viewport.clock) / CLOCKS_PER_SEC;

        if (render_delta > (1.0 / 60.0)) {
            viewport.update(render_delta, camera.update);
            msleep(10);
        }    
    }

    return 0;
}