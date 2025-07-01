#ifndef CAMERA_H
#define CAMERA_H

#include "utils/cmath.h"
#include "window.h"

typedef struct GLR_Camera
{
    Mat4 projection;
    Mat4 view;
    Mat4 camera_matrix;
    Vec3 position;
} GLR_Camera, Camera;

GLR_Camera camera;

int glc_camera(float fov, GLR_AspectRatios aspect, float near_plane, float far_plane)
{
    camera.projection = mat4_perspective(cmath_to_radians(fov), glr_get_virtual_aspect(aspect), near_plane, far_plane);
    camera.view = mat4_look_at(camera.position, vec3_add(camera.position, vec3(0.0f, 0.0f, -1.0f)));
    camera.camera_matrix = mat4_multiply(camera.projection, camera.view);

    return 0;
}

#endif