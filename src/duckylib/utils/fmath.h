#ifndef FMATH_H
#define FMATH_H

#include <math.h>
#include "mat4.h"
#include "vec3.h"
#include "vec2.h"
#include "vec4.h"

#define M_PI 3.14159265358979323846

float fmath_to_radians(float value);

Vec2 fmath_v3_to_v2(Vec3 value);
Vec3 fmath_v2_to_v3(Vec2 value, float z_value);

#endif
