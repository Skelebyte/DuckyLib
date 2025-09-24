#include "../utils/fmath.h"

float fmath_to_radians(float value)
{
    return value * M_PI / 180;
}

Vec2 fmath_v3_to_v2(Vec3 value)
{
    return vec2(value.x, value.y);
}

Vec3 fmath_v2_to_v3(Vec2 value, float z_value)
{
    return vec3(value.x, value.y, z_value);
}