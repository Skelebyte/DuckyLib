#ifndef DUCKY_H
#define DUCKY_H

#define GLAD_GL_IMPLEMENTATION
#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "duckylib/window.h"
#include "duckylib/renderer.h"
#include "duckylib/texture.h"
#include "duckylib/material.h"
#include "duckylib/camera.h"
#include "duckylib/entity.h"
#include "duckylib/ui_entity.h"
#include "duckylib/sound.h"
#include "duckylib/time.h"
#include "duckylib/constants.h"
#include "duckylib/input.h"
#include "duckylib/utils/cmath.h"
#include "duckylib/utils/file.h"
#include "duckylib/utils/mat4.h"
#include "duckylib/utils/vec2.h"
#include "duckylib/utils/vec3.h"
#include "duckylib/utils/vec4.h"

int dl_startup(DL_Window *window, bool init_camera, bool opengl_settings)
{
    if(window != NULL)
    {
        if (dl_window_create(window, "DuckyLib", 800, 600))
        {
            printf("window failed\n");
        }


    }

    SDL_GL_SetSwapInterval(1);

    if (opengl_settings != false)
    {
        dl_renderer_enable_transparency(true);
        dl_renderer_enable_depth_test(true);
        dl_renderer_enable_culling(false);
        dl_renderer_enable_antialiasing(true);
    }

    if(init_camera != false)
    {
        dl_camera_new(75.0f, DL_Aspect_1920x1080, 0.1f, 1000.0f);
    }

    return 0;
}

#endif