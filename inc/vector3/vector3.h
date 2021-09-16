#ifndef __VECTOR3_H
#define __VECTOR3_H

#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} vec3;

extern struct __Vector3Methods {
    vec3 (*new)(double x, double y, double z);
    double (*mag)(vec3* vector);
    vec3 (*unit)(vec3* vector);
    vec3 (*add)(vec3* input1, vec3* input2);
    vec3 (*sub)(vec3* input1, vec3* input2);
    vec3 (*mul)(vec3* input1, vec3* input2, double* number);
    vec3 (*div)(vec3* input1, vec3* input2, double* number);
    double (*dot)(vec3* input1, vec3* input2);
    vec3 (*cross)(vec3* input1, vec3* input2);
} Vector3;

#endif