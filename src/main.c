// Solar System

#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, true, true);

    DL_Entity world_entity = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    world_entity.position = vec3(0, 0, -1.0f);
    dl_renderer_unbind_all(&world_entity.renderer);

    DL_UIEntity ui_entity = dl_ui_entity_new(NULL, BM_LINEAR, DL_Aspect_1920x1080, NULL, NULL);
    ui_entity.material.color = vec4(0.54f, 0.74f, 0.13f, 0.5f);
    dl_renderer_unbind_all(&ui_entity.renderer);

    DL_InputAxis vertical = {
        DL_W,
        DL_S
    };

    DL_InputAxis horizontal = {
        DL_D,
        DL_A
    };

    float move_speed = 5.0f;

    while (window.running)
    {
        dl_frame_begin();

        dl_poll_events(&window);

        ui_entity.position.x += dl_get_axis(&window, horizontal) * move_speed * dl_time.delta_time;
        ui_entity.position.y += dl_get_axis(&window, vertical) * move_speed * dl_time.delta_time;

        if(ui_entity.position.x > 1.0f)
            ui_entity.position.x = 1.0f;
        if (ui_entity.position.x < -1.0f)
            ui_entity.position.x = -1.0f;
        if (ui_entity.position.y > 1.0f)
            ui_entity.position.y = 1.0f;
        if (ui_entity.position.y < -1.0f)
            ui_entity.position.y = -1.0f;

        ui_entity.rotation.z += 5 * dl_time.delta_time;

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background(vec3(0.1f, 0.1f, 0.1f));
        dl_renderer_clear();

        dl_camera_update();
        dl_entity_update(&world_entity);
        dl_ui_entity_update(&ui_entity);

        dl_window_swap_buffer(&window);
        dl_frame_end();

    }
    dl_entity_destroy(&world_entity);
    dl_ui_entity_destroy(&ui_entity);
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();
    return 0;
}