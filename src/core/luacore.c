#include "luacore.h"

static void* __RunFile(void* args) {
    lua.state = luaL_newstate();
    luaL_openlibs(lua.state);

    luaL_dofile(lua.state, (char*) args);
}


struct __Lua lua = {
    .runfile = __RunFile
};