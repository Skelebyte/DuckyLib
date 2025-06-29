#ifndef MAT4_H
#define MAT4_H

#include <math.h>
#include "vec3.h"

#define M_PI 3.14159265358979323846

/**
 * Matrix 4x4
 */
typedef struct Mat4
{
    float matrix[4][4];

} Mat4, Matrix4x4;

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

    mat4.matrix[0][0] = 1.0f;
    mat4.matrix[1][1] = 1.0f;
    mat4.matrix[2][2] = 1.0f;
    mat4.matrix[3][3] = 1.0f;

    return mat4;
}

Mat4 mat4_multiply(Mat4 a, Mat4 b)
{
    Mat4 temp = mat4_identity();
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            temp.matrix[r][c] = 0;

            for (int i = 0; i < 4; i++)
            {
                temp.matrix[r][c] += a.matrix[r][i] * b.matrix[i][c];
            }
        }
    }

    temp.matrix[3][3] = 1.0f;

    return temp;
}

int mat4_translate(Mat4 *mat4, Vec3 point)
{
    mat4->matrix[0][3] = point.x;
    mat4->matrix[1][3] = point.y;
    mat4->matrix[2][3] = point.z;
}

int mat4_rotate(Mat4 *mat4, Vec3 angles)
{
    Mat4 x_rot;
    Mat4 y_rot;
    Mat4 z_rot;
    Mat4 temp;
    Vec3 angles_in_rad = vec3(angles.x * M_PI / 180, angles.y * M_PI / 180, angles.z * M_PI / 180);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            x_rot.matrix[i][j] = mat4->matrix[i][j];
            y_rot.matrix[i][j] = mat4->matrix[i][j];
            z_rot.matrix[i][j] = mat4->matrix[i][j];
        }
    }

    x_rot.matrix[1][1] = cos(angles_in_rad.x);
    x_rot.matrix[2][1] = sin(angles_in_rad.x);
    x_rot.matrix[1][2] = -sin(angles_in_rad.x);
    x_rot.matrix[2][2] = cos(angles_in_rad.x);

    y_rot.matrix[0][0] = cos(angles_in_rad.y);
    y_rot.matrix[2][0] = -sin(angles_in_rad.y);
    y_rot.matrix[0][2] = sin(angles_in_rad.y);
    y_rot.matrix[2][2] = cos(angles_in_rad.y);

    z_rot.matrix[0][0] = cos(angles_in_rad.z);
    z_rot.matrix[1][0] = -sin(angles_in_rad.z);
    z_rot.matrix[0][1] = sin(angles_in_rad.z);
    z_rot.matrix[1][1] = cos(angles_in_rad.z);

    temp = (mat4_multiply(mat4_multiply(x_rot, y_rot), z_rot));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat4->matrix[i][j] = temp.matrix[i][j];
        }
    }
    return 0;
}

int mat4_scale(Mat4 *mat4, Vec3 scale)
{
    mat4->matrix[0][0] = scale.x;
    mat4->matrix[1][1] = scale.y;
    mat4->matrix[2][2] = scale.z;

    return 0;
}

Mat4 mat4_custom(Vec3 pos, Vec3 rot, Vec3 sca)
{
    Mat4 temp;

    Mat4 position = mat4_identity();
    Mat4 rotation = mat4_identity();
    Mat4 scale = mat4_identity();

    mat4_translate(&position, pos);
    mat4_rotate(&rotation, rot);
    mat4_scale(&scale, sca);

    //Mat4 new_matrix = mat4_multiply(mat4_multiply(scale, rotation), position);
    Mat4 new_matrix = mat4_multiply(position, mat4_multiply(scale, rotation));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp.matrix[i][j] = new_matrix.matrix[i][j];
        }
    }

    return temp;
}

Mat4 mat4()
{
    return mat4_identity();
}

#endif