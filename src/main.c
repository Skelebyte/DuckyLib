#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, true, true);

    Entity entity = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    entity.position = vec3(0.0f, 1.0f, 0.0f);
    dl_material_new(&entity.material, "data/textures/frank.png", GL_LINEAR, DL_WHITE);
    dl_renderer_unbind_all(&entity.renderer);

    Entity entity2 = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    entity2.position = vec3(0.0f, -1.0f, 0.0f);
    entity2.rotation = vec3(90.0f, 0.0f, 0.0f);
    entity2.scale = vec3(10.0f, 10.0f, 10.0f);
    dl_renderer_unbind_all(&entity2.renderer);

    int z = 0;

    InputAxis vertical = {
        DL_S,
        DL_W
    };
    InputAxis horizontal = {
        DL_D,
        DL_A
    };
    InputAxis up_down = {
        DL_Q,
        DL_E
    };

    while (window.running)
    {
        dl_frame_begin();
        while (SDL_PollEvent(&window.sdl_event))
        {
            dl_poll_events(&window);
        }
        camera.position.z += dl_get_axis(&window, vertical) * time.delta_time;
        camera.position.x += dl_get_axis(&window, horizontal) * time.delta_time;
        camera.position.y += dl_get_axis(&window, up_down) * time.delta_time;

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background((Vec4){0.1f, 0.1f, 0.1f, 1.0f});
        dl_renderer_clear();

        dl_entity_update(&entity);
        dl_entity_update(&entity2);

        dl_camera_update();
        dl_window_swap_buffer(&window);
        dl_frame_end();
    }

    dl_entity_destroy(&entity);
    dl_entity_destroy(&entity2);
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();
    return 0;
}