#include "luacore.h"

// LUAC GAMEOBJECT

static int __Create(lua_State* state) {
    const char* name = luaL_checkstring(state, -1);
    lua_newtable(state);
    lua_pushstring(state, name);
    lua_setfield(state, 2, "name");

    return 1;
}

static const luaL_Reg gameobjectlib[] = {
    {"create", __Create},
    {NULL, NULL}
};

static void* __RunFile(void* args) {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);

    luaL_dofile(state, (char*) args);
    printf("Finished executing %s\n", (char*) args);
}


struct __Lua lua = {
    .runfile = __RunFile
};