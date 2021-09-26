#ifndef __LUACORE_H
#define __LUACORE_H

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <pthread.h>

extern struct __Lua {
    void* (*runfile)(void* args);
} lua;

#endif