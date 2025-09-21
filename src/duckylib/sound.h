#ifndef SOUND_H
#define SOUND_H

#include <stdbool.h>
#include "camera.h"
#include "utils/vec3.h"
#include "miniaudio/miniaudio.h"

typedef struct DL_SoundEngine
{
    ma_engine engine;

    ma_result _result;
} DL_SoundEngine, SoundEngine;

typedef struct DL_Sound
{
    bool playing;

    ma_sound _sound;
    ma_uint64 _millis;
    ma_result _result;
} DL_Sound, Sound;

int dl_sound_engine_new(DL_SoundEngine *engine);

void dl_sound_engine_destroy(DL_SoundEngine *engine);

int dl_sound_new(DL_SoundEngine *sound_engine, DL_Sound *sound, const char *path, bool is_3d);


void dl_sound_set_position(DL_Sound *sound, Vec3 position);

int dl_sound_play(DL_Sound *sound);

int dl_sound_stop(DL_Sound *sound);

void dl_sound_pause(DL_Sound *sound);

void dl_sound_volume(DL_Sound *sound, float vol);

void dl_sound_pan(DL_Sound *sound, float pan);

#endif
