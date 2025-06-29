#ifndef CMATH_H
#define CMATH_H

#include <math.h>
#include "mat4.h"
#include "vec3.h"

#define M_PI 3.14159265358979323846

float cmath_to_radians(float value)
{
    return value * M_PI / 180;
}

/**
 * @param fieldOfView The field of view in Radians
 */
Mat4 cmath_perspective(float field_of_view, float aspect, float near_plane, float far_plane)
{
    Mat4 temp = {0};

    float tanFov = tanf(field_of_view / 2);
    temp.matrix[0][0] = 1.0f / (aspect * tanFov);
    temp.matrix[1][1] = 1.0f / tanFov;
    temp.matrix[2][2] = -(far_plane + near_plane) / (far_plane - near_plane);
    temp.matrix[2][3] = -1.0f;
    temp.matrix[3][2] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);
    return temp;
}

Vec3 cmath_cross(Vec3 a, Vec3 b)
{
    Vec3 cross = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
    return cross;
}

Mat4 mat4_look_at(Vec3 position, Vec3 target)
{
    // Vec3 forward = (position - target).Normalize();
    Vec3 forward = vec3_normalize(vec3_sub(position, target));
    Vec3 right = vec3_normalize(cmath_cross(vec3(0, 1, 0), forward));

    Vec3 corrected_up = cmath_cross(forward, right);

    Mat4 matrix = mat4();
    // Row 0
    matrix.matrix[0][0] = right.x;
    matrix.matrix[0][1] = right.y;
    matrix.matrix[0][2] = right.z;
    matrix.matrix[0][3] = -vec3_dot(right, position);

    // Row 1
    matrix.matrix[1][0] = corrected_up.x;
    matrix.matrix[1][1] = corrected_up.y;
    matrix.matrix[1][2] = corrected_up.z;
    matrix.matrix[1][3] = -vec3_dot(corrected_up, position);

    // Row 2
    matrix.matrix[2][0] = forward.x;
    matrix.matrix[2][1] = forward.y;
    matrix.matrix[2][2] = forward.z;
    matrix.matrix[2][3] = -vec3_dot(forward, position);

    // Row 3 (homogeneous bottom row)
    matrix.matrix[3][0] = 0.0f;
    matrix.matrix[3][1] = 0.0f;
    matrix.matrix[3][2] = 0.0f;
    matrix.matrix[3][3] = 1.0f;

    return matrix;
}

#endif