#include "../camera.h"

DL_Camera camera;

int dl_camera_new(float fov, DL_AspectRatios aspect, float near_plane, float far_plane)
{

    mat4_perspective(camera.projection, cmath_to_radians(fov), dl_get_virtual_aspect(aspect), near_plane, far_plane);
    mat4_look_at(camera.view, camera.position, vec3_add(camera.position, vec3(0.0f, 0.0f, -1.0f)));
    mat4_multiply(camera.camera_matrix, camera.projection, camera.view);

    return 0;
}

int dl_camera_update()
{
    mat4_look_at(camera.view, camera.position, vec3_add(camera.position, vec3(0.0f, 0.0f, -1.0f)));
    mat4_multiply(camera.camera_matrix, camera.projection, camera.view);

    return 0;
}

int dl_camera_destroy()
{
    camera.position = vec3_zero();
    return 0;
}
