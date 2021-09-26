#ifndef __CAMERA_H
#define __CAMERA_H

#include "vector3/vector3.h"
#include "quaternion/quaternion.h"
#include "core/render/render.h"

static void __Update(double delta);

extern struct __Camera {
    vec3 position;
    vec3 size;
    struct {
        vec3 look_vector;
        vec3 up_vector;
        vec3 right_vector;
    } rotation;

    void (*update)(double delta);
} camera;

#endif
