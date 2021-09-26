CC = gcc

INCLUDE = ./inc
SOURCE = ./src
BUILD = ./build
BINARY = ./bin

LUA = ./lua

CORE = init.o render.o camera.o luacore.o event.o thread.o
UTIL = vector3.o quaternion.o helper.o dynarray.o

all: $(CORE) $(UTIL)
	make -C $(LUA)
	$(CC) $(addprefix $(BUILD)/, $^) -o $(BINARY)/con -llua -L$(LUA) -lm -ldl -lpthread

$(CORE):
	$(CC) -c $(SOURCE)/core/$(basename $@)/$(basename $@).c -o $(BUILD)/$@ -I $(INCLUDE) -I $(SOURCE) -I $(LUA)

$(UTIL):
	$(CC) -c $(INCLUDE)/$(basename $@)/$(basename $@).c -o $(BUILD)/$@ -I $(INCLUDE) -I $(SOURCE) -I $(LUA)
