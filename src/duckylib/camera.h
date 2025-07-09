#ifndef CAMERA_H
#define CAMERA_H

#include "utils/cmath.h"
#include "window.h"

/**
 * @brief `GLR_Camera`
 * @typedef `GLR_Camera`, `Camera`
 *
 */
typedef struct DL_Camera
{
    Mat4 projection;
    Mat4 view;
    Mat4 camera_matrix;
    Vec3 position;
} DL_Camera, Camera;

/**
 * @brief Global camera
 *
 */
DL_Camera camera;

/**
 * @brief Generates the perspective projection view matrices using the global `GLR_Camera camera`.
 * 
 * @param fov Field of view in degrees.
 * @param aspect Aspect ratio
 * @param near_plane Clipping distance close to the camera
 * @param far_plane Clipping distance far from the camera
 * @return int 
 */
int dl_camera_new(float fov, DL_AspectRatios aspect, float near_plane, float far_plane)
{

    mat4_perspective(camera.projection, cmath_to_radians(fov), dl_get_virtual_aspect(aspect), near_plane, far_plane);
    mat4_look_at(camera.view, camera.position, vec3_add(camera.position, vec3(0.0f, 0.0f, -1.0f)));
    mat4_multiply(camera.camera_matrix, camera.projection, camera.view);

    return 0;
}
/**
 * @brief Updates the view matrices using the global `GLR_Camera camera`.
 *
 * @return int 
 */
int dl_camera_update()
{
    mat4_look_at(camera.view, camera.position, vec3_add(camera.position, vec3(0.0f, 0.0f, -1.0f)));
    mat4_multiply(camera.camera_matrix, camera.projection, camera.view);

    return 0;
}

/**
 * @brief uses `mat4_free` to clear all matrices in `GLR_Camera`.
 * 
 * @return int 
 */
int dl_camera_destroy()
{
    camera.position = vec3_zero();
    return 0;
}

#endif