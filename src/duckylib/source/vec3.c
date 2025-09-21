#include "../utils/vec3.h"

Vec3 vec3_zero()
{
    Vec3 zero = {0};
    return zero;
}

Vec3 vec3(float x, float y, float z)
{
    Vec3 vec = {
        x,
        y,
        z};

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
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float vec3_magnitude(Vec3 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vec3 vec3_normalize(Vec3 vec)
{

    if (vec3_magnitude(vec) == 0.0f)
        return vec3_zero();

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