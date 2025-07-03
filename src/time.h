#ifndef TIME_H
#define TIME_H

#include <SDL3/SDL.h>

typedef struct Time
{
    float delta_time;
    int fps;
    int frames;
} Time;

#endif