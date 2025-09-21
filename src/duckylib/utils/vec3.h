#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdbool.h>

typedef union Vec3
{
    struct 
    {
        float x;
        float y;
        float z;
    };
    float data[3];

} Vec3, Vector3;

Vec3 vec3_zero();
Vec3 vec3(float x, float y, float z);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
float vec3_dot(Vec3 a, Vec3 b);
float vec3_length(Vec3 vec);
float vec3_magnitude(Vec3 vec);
Vec3 vec3_normalize(Vec3 vec);
bool vec3_is_equal(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);

#endif