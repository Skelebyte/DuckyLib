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


#endif