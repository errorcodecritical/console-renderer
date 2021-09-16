#include "quaternion.h"

static quat4 __New(double w, vec3 v) {
    return (quat4){w, v};
}

static quat4 __Mul(quat4* input1, quat4* input2) {
    double w1 = input1->w;
    double w2 = input2->w;
    vec3 v1 = input1->v;
    vec3 v2 = input2->v;

    double w_new = w1 * w2 - Vector3.dot(&v1, &v2);

    vec3 v1w2 = Vector3.mul(&v1, 0x0, &w2);
    vec3 v2w1 = Vector3.mul(&v2, 0x0, &w1);
    vec3 v1w2_add_v2w1 = Vector3.add(&v1w2, &v2w1);
    vec3 v1_cross_v2 = Vector3.cross(&v1, &v2);
    vec3 v_new = Vector3.add(&v1_cross_v2, &v1w2_add_v2w1);

    return (quat4){w_new, v_new};
}

static quat4 __Conj(quat4* input1) {
    return (quat4){input1->w, (vec3){-input1->v.x, -input1->v.y, -input1->v.z}};
}

struct __QuaternionMethods Quaternion = {
    .new = __New,
    .mul = __Mul,
    .conjugate = __Conj
};