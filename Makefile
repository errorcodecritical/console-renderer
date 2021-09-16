CC = gcc

INCLUDE = ./inc
SOURCE = ./src
BUILD = ./build
BINARY = ./bin

LUA = ./lua

all: init.o render.o camera.o vector3.o quaternion.o
	$(CC) $(addprefix $(BUILD)/, $^) -o $(BINARY)/con -llua -L$(LUA) -lm -ldl

# CORE

init.o: $(SOURCE)/core/init.c
	$(CC) -c $< -o $(BUILD)/$@ -I $(INCLUDE) -I $(LUA)

render.o: $(SOURCE)/core/render.c
	$(CC) -c $< -o $(BUILD)/$@ -I $(INCLUDE) -I $(LUA)

camera.o: $(SOURCE)/core/camera.c
	$(CC) -c $< -o $(BUILD)/$@ -I $(INCLUDE) -I $(LUA)

# INCLUDE

vector3.o: $(INCLUDE)/vector3/vector3.c
	$(CC) -c $< -o $(BUILD)/$@ -I $(INCLUDE) -I $(LUA)

quaternion.o: $(INCLUDE)/quaternion/quaternion.c
	$(CC) -c $< -o $(BUILD)/$@ -I $(INCLUDE) -I $(LUA)

