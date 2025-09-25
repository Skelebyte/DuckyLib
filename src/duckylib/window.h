#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include "glad/glad.h"
#include "time.h"

typedef enum DL_AspectRatios
{
    DL_Aspect_1920x1080,
    DL_Aspect_1280x720,
    DL_Aspect_960x540,
    DL_Aspect_640x360,
    DL_Aspect_320x180,
    DL_Aspect_256_240,
    DL_Aspect_320x240
} DL_AspectRatios, AspectRatios;

typedef struct DL_Window
{
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_GLContext sdl_glcontext;
    SDL_Event sdl_event;

    float viewport_w;
    float viewport_h;
    int viewport_x;
    int viewport_y;

    bool pillarboxed;
    bool letterboxed;
    bool running;
} DL_Window, Window;

int dl_window_create(DL_Window *window, const char *title, int w, int h);
int dl_poll_events(DL_Window *window);
float dl_get_virtual_aspect(DL_AspectRatios virtual_aspect);
void dl_window_set_viewport(DL_Window *window, DL_AspectRatios virtual_aspect);
void dl_window_set_name(DL_Window *window, const char *name);
int dl_window_swap_buffer(DL_Window *window);
int dl_window_destroy(DL_Window *window);

#endif
