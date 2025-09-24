#ifndef CAMERA_H
#define CAMERA_H

#include "utils/fmath.h"
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
extern DL_Camera camera;

/**
 * @brief Generates the perspective projection view matrices using the global `GLR_Camera camera`.
 *
 * @param fov Field of view in degrees.
 * @param aspect Aspect ratio
 * @param near_plane Clipping distance close to the camera
 * @param far_plane Clipping distance far from the camera
 * @return int
 */
int dl_camera_new(float fov, DL_AspectRatios aspect, float near_plane, float far_plane);
/**
 * @brief Updates the view matrices using the global `GLR_Camera camera`.
 *
 * @return int
 */
int dl_camera_update();

int dl_camera_destroy();

#endif
