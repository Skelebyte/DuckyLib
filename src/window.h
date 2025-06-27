#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include "glad/glad.h"

typedef struct GLR_Window
{
    SDL_Window *sdl_window;
    SDL_GLContext sdl_glcontext;
    SDL_Event sdl_event;
} GLR_Window, Window;

int glr_window_create(GLR_Window *window, const char *title, int w, int h)
{
    printf("bos");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

    return 0;
}

int glr_window_should_close(GLR_Window *window)
{
    while (SDL_PollEvent(&window->sdl_event))
    {
        if (window->sdl_event.type == SDL_EVENT_QUIT)
            return 1;
    }
    return 0;
}

int glr_window_swap_buffer(GLR_Window *window)
{
    SDL_GL_SwapWindow(window->sdl_window);
    return 0;
}

int glr_window_destroy(GLR_Window *window)
{
    SDL_GL_DestroyContext(window->sdl_glcontext);
    SDL_DestroyWindow(window->sdl_window);
    return 0;
}

#endif