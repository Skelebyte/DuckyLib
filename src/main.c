#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, "DuckyLib", true, true);

    if(TTF_Init() == -1)
    {
        const char *err = SDL_GetError();
        fprintf(stderr, "ttf init failed: %s\n", err);
        dl_window_destroy(&window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("data/fonts/OpenSans-Regular.ttf", 64);
    if(font == NULL)
    {
        printf("font is null!\n");
        dl_window_destroy(&window);
        SDL_Quit();
        return 2;
    }
    // SDL_Color color = {255, 255, 255, 255};
    // SDL_Surface *surface = TTF_RenderText_Solid_Wrapped(font, "DuckyLib! DuckyLib! DuckyLib! this is cool.", 45, color, 400);
    // DL_Texture text;
    // dl_texture_data_load(&text, surface->pixels, BM_LINEAR);

    // SDL_Texture *texture = SDL_CreateTextureFromSurface(window.sdl_renderer, message);
    // float w, h;
    // SDL_GetTextureSize(texture, &w, &h);
    // SDL_FRect textRect;
    // textRect.x = 0;
    // textRect.y = 0;
    // textRect.w = w;
    // textRect.h = h;

    DL_Entity entity = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    dl_material_new(&entity.material, DL_DEFAULT_TEXTURE, BM_NEAREST, DL_WHITE, false);
    entity.position.z = -1;

    while (window.running)
    {
        dl_frame_begin();

        dl_poll_events(&window);

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background(vec4(0.6f, 0.1f, 0.1f, 1.0f));
        dl_renderer_clear();

        dl_camera_update();
        dl_entity_update(&entity);
        // SDL_RenderClear(window.sdl_renderer);
        // SDL_RenderTexture(window.sdl_renderer, texture, NULL, &textRect);
        // SDL_RenderPresent(window.sdl_renderer);

        //dl_entity_update(&entity);

        dl_window_swap_buffer(&window);
        dl_frame_end();
    }
    TTF_Quit();
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();


    return 0;
}
