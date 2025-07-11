#ifndef MAT4_H
#define MAT4_H

#include <math.h>
#include <stdlib.h>
#include "vec3.h"

#define M_PI 3.14159265358979323846

typedef enum Mat4_TransformationOrder
{
    Mat4_PRS,
    Mat4_PSR,
    Mat4_RSP,
    Mat4_RPS,
    Mat4_SRP,
    Mat4_SPR,
} Mat4_TransformationOrder, TransformationOrder;

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
void mat4_identity(Mat4 mat4)
{
    for (int i = 0; i < 16; i++)
        mat4[i] = 0;

    mat4[0] = 1;
    mat4[5] = 1;
    mat4[10] = 1;
    mat4[15] = 1;
}

void mat4_multiply(Mat4 out, Mat4 a, Mat4 b)
{
    mat4_identity(out);

    for (int row = 0; row < 4; row++) 
    {
        for (int col = 0; col < 4; col++) 
        {
            float sum = 0;
            for (int i = 0; i < 4; i++) 
            {
                sum += a[i * 4 + row] * b[col * 4 + i];
            }
            out[col * 4 + row] = sum;
        }
    }
}

void mat4_translate(Mat4 out, Vec3 point)
{
    out[12] = point.x;
    out[13] = point.y;
    out[14] = point.z;
}

void mat4_rotate(Mat4 out, Vec3 angles)
{
    Mat4 x_rot;
    mat4_identity(x_rot);
    Mat4 y_rot;
    mat4_identity(y_rot);
    Mat4 z_rot;
    mat4_identity(z_rot);
    Vec3 angles_in_rad = vec3(angles.x * M_PI / 180, angles.y * M_PI / 180, angles.z * M_PI / 180);
    // for (int i = 0; i < 16; i++)
    // {
    //     x_rot[i] = mat4[i];
    //     y_rot[i] = mat4[i];
    //     z_rot[i] = mat4[i];
    // }

    x_rot[5] = cos(angles_in_rad.x);
    x_rot[6] = -sin(angles_in_rad.x);
    x_rot[9] = sin(angles_in_rad.x);
    x_rot[10] = cos(angles_in_rad.x);

    y_rot[0] = cos(angles_in_rad.y);
    y_rot[2] = sin(angles_in_rad.y);
    y_rot[8] = -sin(angles_in_rad.y);
    y_rot[10] = cos(angles_in_rad.y);

    z_rot[0] = cos(angles_in_rad.z);
    z_rot[1] = sin(angles_in_rad.z);
    z_rot[4] = -sin(angles_in_rad.z);
    z_rot[5] = cos(angles_in_rad.z);

    Mat4 xy_rot;
    mat4_multiply(xy_rot, x_rot, y_rot);
    Mat4 xyz_rot;
    mat4_multiply(xyz_rot, xy_rot, z_rot);
    Mat4 rot;
    mat4_multiply(rot, out, xyz_rot);
    for (int i = 0; i < 16; i++)
    {
        out[i] = rot[i];
    }
}

void mat4_scale(Mat4 out, Vec3 scale)
{
    out[0] = scale.x;
    out[5] = scale.y;
    out[10] = scale.z;

}

void mat4_custom(Mat4 out, Vec3 pos, Vec3 rot, Vec3 sca, Mat4_TransformationOrder order)
{

    mat4_identity(out);

    Mat4 position;
    mat4_identity(position);
    Mat4 rotation;
    mat4_identity(rotation);
    Mat4 scale;
    mat4_identity(scale);

    mat4_translate(position, pos);
    mat4_rotate(rotation, rot);
    mat4_scale(scale, sca);

    Mat4 half_matrix;
    switch(order)
    {
        case Mat4_PRS:
            mat4_multiply(half_matrix, rotation, scale);
            mat4_multiply(out, position, half_matrix);
        case Mat4_PSR:
            mat4_multiply(half_matrix, scale, rotation);
            mat4_multiply(out, position, half_matrix);
        case Mat4_RPS:
            mat4_multiply(half_matrix, position, scale);
            mat4_multiply(out, rotation, half_matrix);
        case Mat4_RSP:
            mat4_multiply(half_matrix, scale, position);
            mat4_multiply(out, rotation, half_matrix);
        case Mat4_SPR:
            mat4_multiply(half_matrix, position, rotation);
            mat4_multiply(out, scale, half_matrix);
        case Mat4_SRP:
            mat4_multiply(half_matrix, rotation, position);
            mat4_multiply(out, scale, half_matrix);
    }

}

void mat4_perspective(Mat4 out, float fov_in_rads, float aspect, float near_plane, float far_plane)
{
    mat4_identity(out);

    out[0] = 1 / (aspect * tan(fov_in_rads / 2));
    out[5] = 1 / tan(fov_in_rads / 2);
    out[10] = -(far_plane + near_plane) / (far_plane - near_plane);
    out[11] = -1;
    out[14] = -(2 * far_plane * near_plane) / (far_plane - near_plane);
    out[15] = 0;
}

void mat4_look_at(Mat4 out, Vec3 position, Vec3 targetPosition)
{
    mat4_identity(out);
    Vec3 forward = vec3_normalize(vec3_sub(position, targetPosition));
    Vec3 right = vec3_normalize(vec3_cross(vec3(0.0f, 1.0f, 0.0f), forward));
    Vec3 up = vec3_cross(forward, right);

    out[0] = right.x;
    out[4] = right.y;
    out[8] = right.z;
    out[12] = -vec3_dot(right, position);

    out[1] = up.x;
    out[5] = up.y;
    out[9] = up.z;
    out[13] = -vec3_dot(up, position);

    out[2] = forward.x;
    out[6] = forward.y;
    out[10] = forward.z;
    out[14] = -vec3_dot(forward, position);
}

#endif