#ifndef TIME_H
#define TIME_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct Time
{
    float delta_time;

    double _first_frame;
    double _last_frame;

} Time;

Time time = {0};

int glt_init_time()
{
    time._last_frame = SDL_GetTicks();
    time._last_frame /= 1000;

    return 0;
}

int glt_begin_frame()
{
    time._first_frame = SDL_GetTicks();
    time._first_frame /= 1000;

    return 0;
}

int glt_end_frame()
{
    time._last_frame = SDL_GetTicks();
    time._last_frame /= 1000;

    time.delta_time = time._last_frame - time._first_frame;

    return 0;
}

#endif