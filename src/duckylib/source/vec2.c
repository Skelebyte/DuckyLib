#include "../utils/vec2.h"

Vec2 vec2_zero()
{
    Vec2 zero = {0};
    return zero;
}

Vec2 vec2(float x, float y)
{
    Vec2 vec = {
        x,
        y,
    };

    return vec;
}

Vec2 vec2_add(Vec2 a, Vec2 b)
{
    a.x += b.x;
    a.y += b.y;

    return a;
}

Vec2 vec2_sub(Vec2 a, Vec2 b)
{
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

float vec2_dot(Vec2 a, Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

float vec2_length(Vec2 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float vec2_magnitude(Vec2 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vec2 vec2_normalize(Vec2 vec)
{

    if (vec2_magnitude(vec) == 0.0f)
        return vec2_zero();

    Vec2 b = {
        vec.x / vec2_magnitude(vec),
        vec.y / vec2_magnitude(vec),
    };

    return b;
}

bool vec2_is_equal(Vec2 a, Vec2 b)
{
    return (a.x == b.x && a.y == b.y);
}

Vec2 vec2_cross(Vec2 a, Vec2 b)
{
    Vec2 cross = {
        a.y * b.x - a.x * b.y,
        a.y * b.x - a.x * b.y,
    };
    return cross;
}

float vec2_distance(Vec2 a, Vec2 b)
{
    return sqrt(pow((b.x - a.x), 2) + pow((b.y, a.y), 2));
}