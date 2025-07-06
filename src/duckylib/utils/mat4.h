#ifndef MAT4_H
#define MAT4_H

#include <math.h>
#include <stdlib.h>
#include "vec3.h"

#define M_PI 3.14159265358979323846

#define Mat4 float*

int mat4_free(Mat4 mat4) 
{
    free(mat4);
    return 0;
}

/**
 * @brief Default value for a 4x4 matrix.
 * @code {.c}
 * 1, 0, 0, 0,
 * 0, 1, 0, 0,
 * 0, 0, 1, 0,
 * 0, 0, 0, 1,
 * @endcode
 */
Mat4 mat4_identity()
{
    Mat4 mat4;

    mat4 = malloc(sizeof(float) * 16);

    for (int i = 0; i < 16; i++)
        mat4[i] = 0;

    mat4[0] = 1;
    mat4[5] = 1;
    mat4[10] = 1;
    mat4[15] = 1;

    return mat4;
}

Mat4 mat4_multiply(Mat4 a, Mat4 b)
{
    Mat4 temp = mat4_identity();

    for (int row = 0; row < 4; row++) 
    {
        for (int col = 0; col < 4; col++) 
        {
            float sum = 0;
            for (int i = 0; i < 4; i++) 
            {
                sum += a[i * 4 + row] * b[col * 4 + i];
            }
            temp[col * 4 + row] = sum;
        }
    }

    return temp;
}

int mat4_translate(Mat4 mat4, Vec3 point)
{
    mat4[12] = point.x;
    mat4[13] = point.y;
    mat4[14] = point.z;

    return 0;
}

int mat4_rotate(Mat4 mat4, Vec3 angles)
{
    Mat4 x_rot = mat4_identity();
    Mat4 y_rot = mat4_identity();
    Mat4 z_rot = mat4_identity();
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

    Mat4 xy_rot = mat4_multiply(x_rot, y_rot);
    Mat4 xyz_rot = mat4_multiply(xy_rot, z_rot);
    Mat4 rot = mat4_multiply(mat4, xyz_rot);
    for (int i = 0; i < 16; i++)
    {
        mat4[i] = rot[i];
    }
    mat4_free(rot);
    mat4_free(xy_rot);
    mat4_free(xyz_rot);
    return 0;
}

int mat4_scale(Mat4 mat4, Vec3 scale)
{
    mat4[0] = scale.x;
    mat4[5] = scale.y;
    mat4[10] = scale.z;

    return 0;
}

Mat4 mat4_custom(Vec3 pos, Vec3 rot, Vec3 sca)
{
    Mat4 position = mat4_identity();
    Mat4 rotation = mat4_identity();
    Mat4 scale = mat4_identity();

    mat4_translate(position, pos);
    mat4_rotate(rotation, rot);
    mat4_scale(scale, sca);

    Mat4 new_matrix = mat4_multiply(position, mat4_multiply(rotation, scale));

    mat4_free(position);
    mat4_free(rotation);
    mat4_free(scale);

    return new_matrix;
}

Mat4 mat4_perspective(float fov_in_rads, float aspect, float near_plane, float far_plane) 
{
    Mat4 temp = mat4_identity();

    temp[0] = 1 / (aspect * tan(fov_in_rads / 2));
    temp[5] = 1 / tan(fov_in_rads / 2);
    temp[10] = -(far_plane + near_plane) / (far_plane - near_plane);
    temp[11] = -1;
    temp[14] = -(2 * far_plane * near_plane) / (far_plane - near_plane);
    temp[15] = 0;

    return temp;
}

Mat4 mat4_look_at(Vec3 position, Vec3 targetPosition) 
{

    Vec3 forward = vec3_normalize(vec3_sub(position, targetPosition));
    Vec3 right = vec3_normalize(vec3_cross(vec3(0.0f, 1.0f, 0.0f), forward));
    Vec3 up = vec3_cross(forward, right);

    Mat4 temp = mat4_identity();

    temp[0] = right.x;
    temp[4] = right.y;
    temp[8] = right.z;
    temp[12] = -vec3_dot(right, position);

    temp[1] = up.x;
    temp[5] = up.y;
    temp[9] = up.z;
    temp[13] = -vec3_dot(up, position);

    temp[2] = forward.x;
    temp[6] = forward.y;
    temp[10] = forward.z;
    temp[14] = -vec3_dot(forward, position);

    return temp;
}

#endif