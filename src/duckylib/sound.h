#ifndef SOUND_H
#define SOUND_H

#include <stdbool.h>
#include "camera.h"
#include "utils/vec3.h" 
#define MINIAUDIO_IMPLEMENTATION
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

int dl_sound_engine_new(DL_SoundEngine *engine)
{

    engine->_result = ma_engine_init(NULL, &engine->engine);

    if(engine->_result != MA_SUCCESS)
    {
        fprintf(stderr, "Miniaudio Engine failed to initialize!\n");
        return 1;
    }

    return 0;
}

void dl_sound_engine_destroy(DL_SoundEngine *engine)
{
    ma_engine_uninit(&engine->engine);
}

int dl_sound_new(DL_SoundEngine *sound_engine, DL_Sound *sound, const char *path, bool is_3d)
{

    sound->_result = ma_sound_init_from_file(&sound_engine->engine, path, 0, NULL, NULL, &sound->_sound);
    if (sound->_result != MA_SUCCESS)
    {
        fprintf(stderr, "Failed to init sound! %d\n", sound->_result);
        return 1;
    }
    sound->playing = false;
    ma_sound_set_spatialization_enabled(&sound->_sound, is_3d);

    return 0;
}


void dl_sound_set_position(DL_Sound *sound, Vec3 position)
{
    Vec3 pos = vec3_add(position, camera.position);
    ma_sound_set_position(&sound->_sound, pos.x, pos.y, pos.z);
}

int dl_sound_play(DL_Sound *sound)
{
    if(sound->playing == true)
        return 1;

    sound->_result = ma_sound_start(&sound->_sound);
    if(sound->_result != MA_SUCCESS)
    {
        fprintf(stderr, "Failed to start sound!\n");
        return 0;
    }
    sound->playing = true;
    return 1;
}

int dl_sound_stop(DL_Sound *sound)
{
    sound->_result = ma_sound_stop(&sound->_sound);
    if(sound->_result != MA_SUCCESS)
    {
        fprintf(stderr, "Failed to stop sound!\n");
        return sound->_result;
    }
    sound->playing = false;
    return 0;
}

void dl_sound_pause(DL_Sound *sound)
{
    sound->_millis = ma_sound_get_time_in_milliseconds(&sound->_sound);
    dl_sound_stop(sound);
}

void dl_sound_volume(DL_Sound *sound, float vol)
{
    ma_sound_set_volume(&sound->_sound, vol);
}

void dl_sound_pan(DL_Sound *sound, float pan)
{
    ma_sound_set_pan(&sound->_sound, pan);
}

#endif