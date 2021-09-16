#ifndef __QUATERNION_H
#define __QUATERNION_H

#include <math.h>
#include "vector3/vector3.h"

typedef struct {
    double w;
    vec3 v;
} quat4;

extern struct __QuaternionMethods {
    quat4 (*new)(double w, vec3 v);
    quat4 (*mul)(quat4* input1, quat4* input2);
    quat4 (*conjugate)(quat4* input1);
} Quaternion;

#endif