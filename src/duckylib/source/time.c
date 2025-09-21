#include "../time.h"

DL_Time dl_time = {0};

void
dl_frame_init()
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
