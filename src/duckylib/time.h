#ifndef TIME_H
#define TIME_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct DL_Time
{
    int fps;
    float delta_time;

    double _first_frame;
    double _last_frame;

    float _counted_frames;
    float _frame_time;

} DL_Time, Time;

DL_Time dl_time = {0};

void dl_frame_init()
{
    dl_time._last_frame = SDL_GetTicks();
    dl_time._last_frame /= 1000;
}

void dl_frame_begin()
{
    dl_time._first_frame = SDL_GetTicks();
    dl_time._first_frame /= 1000;
}

void dl_frame_end()
{
    dl_time._last_frame = SDL_GetTicks();
    dl_time._last_frame /= 1000;

    dl_time.delta_time = dl_time._last_frame - dl_time._first_frame;

    dl_time._counted_frames++;
    dl_time._frame_time += dl_time.delta_time;

    if(dl_time._frame_time >= 1.0f)
    {
        dl_time.fps = dl_time._counted_frames;
        dl_time._frame_time = 0;
        dl_time._counted_frames = 0;
    }

    
}

#endif