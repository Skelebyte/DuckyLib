#ifndef TIME_H
#define TIME_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct Time
{
    int fps;
    float delta_time;

    double _first_frame;
    double _last_frame;

    float _counted_frames;
    float _frame_time;

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

    time._counted_frames++;
    time._frame_time += time.delta_time;

    if(time._frame_time >= 1.0f)
    {
        time.fps = time._counted_frames;
        time._frame_time = 0;
        time._counted_frames = 0;
    }

    return 0;
}

#endif