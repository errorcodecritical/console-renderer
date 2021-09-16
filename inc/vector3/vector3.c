#include "vector3.h"

static vec3 __New(double x, double y, double z) {
    return (vec3){x, y, z};
}

static double __Magnitude(vec3* vector) {
    return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}

static vec3 __Unit(vec3* vector) {
    double mag = __Magnitude(vector);
    return (vec3){vector->x / mag, vector->y / mag, vector->z / mag};
}

static vec3 __Add(vec3* input1, vec3* input2) {
    return (vec3) {input1->x + input2->x,  input1->y + input2->y, input1->z + input2->z};
}

static vec3 __Subtract(vec3* input1, vec3* input2) {
    return (vec3) {input1->x - input2->x,  input1->y - input2->y, input1->z - input2->z};
}

static vec3 __Multiply(vec3* input1, vec3* input2, double* number) {
    if (input2 == 0x0) {
        return (vec3) {input1->x * (*number),  input1->y * (*number), input1->z * (*number)};
    } else {
        return (vec3) {input1->x * input2->x,  input1->y * input2->y, input1->z * input2->z};
    }
}

static vec3 __Divide(vec3* input1, vec3* input2, double* number) {
    if (input2 == 0x0) {
        return (vec3) {input1->x / (*number),  input1->y / (*number), input1->z / (*number)};
    } else {
        return (vec3) {input1->x / input2->x,  input1->y / input2->y, input1->z / input2->z};
    }
}

static double __Dot(vec3* input1, vec3* input2) {
    return (input1->x * input2->x + input1->y * input2->y + input1->z * input2->z);
}

static vec3 __Cross(vec3* input1, vec3* input2) {
    return (vec3){
        (input1->y * input2->z - input1->z * input2->y),
        (input1->z * input2->x - input1->x * input2->z),
        (input1->x * input2->y - input1->y * input2->x)
    };
}

struct __Vector3Methods Vector3 = {
    .new = __New,
    .mag = __Magnitude,
    .unit = __Unit,
    .add = __Add,
    .sub = __Subtract,
    .mul = __Multiply,
    .div = __Divide,
    .dot = __Dot,
    .cross = __Cross
};