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

Vec3 vec3(float x, float y, float z)
{
    Vec3 vec = {
        x,
        y,
        z
    };

    return vec;
}

Vec3 vec3_add(Vec3 a, Vec3 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

Vec3 vec3_sub(Vec3 a, Vec3 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

float vec3_dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_length(Vec3 vec)
{
    return abs(sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

float vec3_magnitude(Vec3 vec)
{
    return abs(sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

Vec3 vec3_normalize(Vec3 vec)
{

    Vec3 b = {
        vec.x / vec3_magnitude(vec),
        vec.y / vec3_magnitude(vec),
        vec.z / vec3_magnitude(vec),
    };

    return b;
}

bool vec3_is_equal(Vec3 a, Vec3 b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    Vec3 cross = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
    return cross;
}

#endif