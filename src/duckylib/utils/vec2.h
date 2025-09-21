#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include <stdbool.h>

typedef union Vec2
{
    struct 
    {
        float x;
        float y;
    };
    float data[2];

} Vec2, Vector2;

Vec2 vec2_zero();
Vec2 vec2(float x, float y);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
float vec2_dot(Vec2 a, Vec2 b);
float vec2_length(Vec2 vec);
float vec2_magnitude(Vec2 vec);
Vec2 vec2_normalize(Vec2 vec);
bool vec2_is_equal(Vec2 a, Vec2 b);
Vec2 vec2_cross(Vec2 a, Vec2 b);

#endif