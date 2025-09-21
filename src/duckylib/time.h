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

extern DL_Time dl_time;

void dl_frame_init();
void dl_frame_begin();
void dl_frame_end();

#endif
