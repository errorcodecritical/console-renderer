#include "camera.h"

float map(float x, float a, float b, float c, float d) {
    return (x - a) / (b - a) * (d - c) + c;
}

struct Object {
    vec3 vertices[8];
} cube;

struct Object cube = {
    .vertices = {
        {-1, -1, 1}, {1, -1, 1}, {-1, 1, 1}, {1, 1, 1},
        {-1, -1, -1}, {1, -1, -1}, {-1, 1, -1}, {1, 1, -1}
    }
};

static void __Update(double delta) {
    // Clear viewport
    for (unsigned short int x = 0; x < viewport.viewport_size.x; x++) {
        for (unsigned short int y = 0; y < viewport.viewport_size.y; y++) {
            viewport.viewport_buffer[y * viewport.viewport_size.x + x] = L' ';
        }
    }

    vec3 axis_of_rotation = (vec3){0, 1, 0};
    double im_rotation = sin(3.14 / 180);
    quat4 rotate_by = (quat4){cos(3.14 / 180), Vector3.mul(&axis_of_rotation, 0x0, &im_rotation)};
    
    for (int i = 0; i < 8; i++) {
        quat4 vertice = (quat4){0, cube.vertices[i]};
        quat4 half_step = Quaternion.mul(&rotate_by, &vertice);
        quat4 conjugate = Quaternion.conjugate(&rotate_by);
        
        cube.vertices[i] = Quaternion.mul(&half_step, &conjugate).v;
    }

    for (int index = 0; index < sizeof(cube.vertices) / sizeof(vec3); index++) {
        // Convert projected point into camera-relative coordinates
        vec3 relative = Vector3.sub(&cube.vertices[index], &camera.position);

        vec3 projected = (vec3){
            Vector3.dot(&relative, &camera.rotation.right_vector),
            Vector3.dot(&relative, &camera.rotation.up_vector),
            Vector3.dot(&relative, &camera.rotation.look_vector)
        };

        float size_x = (float)viewport.viewport_size.x;
        float size_y = (float)viewport.viewport_size.y;

        float z_offset = 10.0;

        projected.x *= z_offset / (z_offset + projected.z);
        projected.y *= z_offset / (z_offset + projected.z);

        float aspect = size_x / size_y;
        
        // Check if point is within viewport bounds
        if ((fabs(projected.x) < (aspect / 2.0)) && (fabs(projected.y) < (1.0)) && (projected.z > 0)) {

            int x_pos = (int)roundf(map(projected.x, -aspect / 2.0, aspect / 2.0, 0.0, size_x));
            int y_pos = (int)roundf(map(projected.y, -1.0, 1.0, 0.0, size_y));

            viewport.viewport_buffer[y_pos * viewport.viewport_size.x + x_pos] = L'#';
        }
    }
}

struct __Camera camera = {
    .position = (vec3){0, 0, 4}, 
    .size = (vec3){2, 2, 2},
    .rotation = {
        .look_vector = (vec3){0, 0, -1}, 
        .up_vector = (vec3){0, 1, 0}, 
        .right_vector = (vec3){1, 0, 0}
    },
    .update = __Update
};