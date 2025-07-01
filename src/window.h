#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include "glad/glad.h"

typedef enum GLR_AspectRatios
{
    GLR_1920x1080,
    GLR_1280x720,
    GLR_960x540,
    GLR_640x360,
    GLR_320x180,
    GLR_256_240,
    GLR_320x240
} GLR_AspectRatios, AspectRatios;

typedef struct GLR_Window
{
    SDL_Window *sdl_window;
    SDL_GLContext sdl_glcontext;
    SDL_Event sdl_event;

    bool running;
} GLR_Window, Window;

int glr_window_create(GLR_Window *window, const char *title, int w, int h)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    window->sdl_window = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window->sdl_window == NULL)
    {
        printf("Failed to create window!\n");
        SDL_Quit();
        return 1;
    }

    window->sdl_glcontext = SDL_GL_CreateContext(window->sdl_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to load GLAD!");
        SDL_DestroyWindow(window->sdl_window);
        SDL_Quit();
        return 2;
    }

    window->running = true;

    return 0;
}

int glw_poll_events(GLR_Window *window)
{
    if (window->sdl_event.type == SDL_EVENT_QUIT)
        window->running = false;

    return 0;
}

float glr_get_virtual_aspect(GLR_AspectRatios virtual_aspect) 
{
    switch (virtual_aspect)
    {
    case GLR_1920x1080:
        return (float)1920 / 1080;
        break;
    case GLR_1280x720:
        return (float)1280 / 720;
        break;
    case GLR_960x540:
        return (float)960 / 540;
        break;
    case GLR_640x360:
        return (float)640 / 360;
        break;
    case GLR_320x180:
        return (float)320 / 180;
        break;
    case GLR_256_240:
        return (float)256 / 240;
        break;
    case GLR_320x240:
        return (float)320 / 240;
        break;
    }
}

    int glw_window_viewport(GLR_Window *window, GLR_AspectRatios virtual_aspect)
{
    int width, height;
    SDL_GetWindowSize(window->sdl_window, &width, &height);

    float window_aspect = (float)width / height;
    float game_aspect = glr_get_virtual_aspect(virtual_aspect);

    int viewport_w, viewport_h, viewport_x, viewport_y;


    if(window_aspect > game_aspect) 
    { // pillarbox
        viewport_h = height;
        viewport_w = (int)(height * game_aspect);
        viewport_x = (width - viewport_w) / 2;
        viewport_y = 0;
    } else 
    { // letterbox
        viewport_w = width;
        viewport_h = (int)(width / game_aspect);
        viewport_x = 0;
        viewport_y = (height - viewport_h) / 2;
    }

    glViewport(viewport_x, viewport_y, viewport_w, viewport_h);

    return 0;
}

int glw_window_swap_buffer(GLR_Window *window)
{
    SDL_GL_SwapWindow(window->sdl_window);

    SDL_Delay(10);

    return 0;
}

int glw_window_destroy(GLR_Window *window)
{
    SDL_GL_DestroyContext(window->sdl_glcontext);
    SDL_DestroyWindow(window->sdl_window);
    return 0;
}

#endif