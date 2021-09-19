#ifndef __LUACORE_H
#define __LUACORE_H

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <pthread.h>

extern struct __Lua {
    lua_State* state;
    pthread_t context;
    int running;

    void (*init)();
    void* (*runfile)(void* args);
} lua;

#endif