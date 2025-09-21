#ifndef MAT4_H
#define MAT4_H

#include <math.h>
#include <stdlib.h>
#include "vec3.h"

#define M_PI 3.14159265358979323846

typedef enum Mat4_MultiplicationOrder
{
    Mat4_TRS, // `entity` default (`transform * (rotation * scale)`)
    Mat4_TSR, // `ui_entity` default (`transform * (scale * rotation)`)
    Mat4_RST, // `rotation * (scale * transform)`
    Mat4_RTS, // `rotation * (transform * scale)`
    Mat4_SRT, // `scale * (rotation * transform)`
    Mat4_STR, // `scale * (transform * rotation)`
} Mat4_MultiplicationOrder, MultiplicationOrder;

typedef float Mat4[16];

/**
 * @brief Default value for a 4x4 matrix.
 * @code {.c}
 * 1, 0, 0, 0,
 * 0, 1, 0, 0,
 * 0, 0, 1, 0,
 * 0, 0, 0, 1,
 * @endcode
 */
void mat4_identity(Mat4 mat4);

void mat4_multiply(Mat4 out, Mat4 a, Mat4 b);

void mat4_translate(Mat4 out, Vec3 point);

void mat4_rotate(Mat4 out, Vec3 angles);

void mat4_scale(Mat4 out, Vec3 scale);

void mat4_custom(Mat4 out, Vec3 pos, Vec3 rot, Vec3 sca, Mat4_MultiplicationOrder order);

void mat4_perspective(Mat4 out, float fov_in_rads, float aspect, float near_plane, float far_plane);

void mat4_look_at(Mat4 out, Vec3 position, Vec3 targetPosition);

#endif
