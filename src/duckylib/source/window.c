#include "../window.h"

int dl_window_create(DL_Window *window, const char *title, int w, int h)
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

int dl_poll_events(DL_Window *window)
{
    while (SDL_PollEvent(&window->sdl_event))
    {
        if (window->sdl_event.type == SDL_EVENT_QUIT)
            window->running = false;
    }

    return 0;
}

float dl_get_virtual_aspect(DL_AspectRatios virtual_aspect)
{
    switch (virtual_aspect)
    {
    case DL_Aspect_1920x1080:
        return (float)1920 / 1080;
        break;
    case DL_Aspect_1280x720:
        return (float)1280 / 720;
        break;
    case DL_Aspect_960x540:
        return (float)960 / 540;
        break;
    case DL_Aspect_640x360:
        return (float)640 / 360;
        break;
    case DL_Aspect_320x180:
        return (float)320 / 180;
        break;
    case DL_Aspect_256_240:
        return (float)256 / 240;
        break;
    case DL_Aspect_320x240:
        return (float)320 / 240;
        break;
    }
}

void dl_window_set_viewport(DL_Window *window, DL_AspectRatios virtual_aspect)
{
    int width, height;
    SDL_GetWindowSize(window->sdl_window, &width, &height);

    float window_aspect = (float)width / height;
    float game_aspect = dl_get_virtual_aspect(virtual_aspect);



    window->pillarboxed = false;
    window->letterboxed = false;
    if (window_aspect > game_aspect)
    { // pillarbox
        window->viewport_h = height;
        window->viewport_w = (int)(height * game_aspect);
        window->viewport_x = (width - window->viewport_w) / 2;
        window->viewport_y = 0;
        window->pillarboxed = true;
    } else
    { // letterbox
        window->viewport_w = width;
        window->viewport_h = (int)(width / game_aspect);
        window->viewport_x = 0;
        window->viewport_y = (height - window->viewport_h) / 2;
        window->letterboxed = true;
    }

    glViewport(window->viewport_x, window->viewport_y, window->viewport_w, window->viewport_h);
}

void dl_window_set_name(DL_Window *window, const char *name)
{
    SDL_SetWindowTitle(window->sdl_window, name);
}

int dl_window_swap_buffer(DL_Window *window)
{
    SDL_GL_SwapWindow(window->sdl_window);

    //SDL_Delay(10);

    return 0;
}

int dl_window_destroy(DL_Window *window)
{
    SDL_GL_DestroyContext(window->sdl_glcontext);
    SDL_DestroyWindow(window->sdl_window);
    return 0;
}
