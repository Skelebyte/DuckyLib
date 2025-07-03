#ifndef TIME_H
#define TIME_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct Time
{
    unsigned int fps;
    unsigned int target_fps;

    float delta_time;

    float _processed_delta_time;
    double _frame_time;

    double _last_frame;

} Time;

Time time;

int glt_begin_frame()
{
    if(time.target_fps == 0)
        time.target_fps = 60;
    time._frame_time = 1000.0f / time.target_fps;

    return 0;
}

int glt_end_frame()
{
    Uint32 now = SDL_GetTicks();
    Uint32 elapsed = now - time._last_frame;

    if (elapsed < time._frame_time)
    {
        
        SDL_Delay(time._frame_time - elapsed);
    }
    time.delta_time = elapsed / 1000.0f;
    time._last_frame = SDL_GetTicks();

    return 0;
}

#endif