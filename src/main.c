#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, true, true);

    DL_UIEntity ui = dl_ui_entity_new(NULL, BM_LINEAR, DL_Aspect_1920x1080, NULL, NULL);
    ui.scale.x = 0.5f;
    ui.scale.y = 0.5f;
    dl_renderer_unbind_all(&ui.renderer);

    printf("%f\n", ui.aspect_ratio);

    DL_Bind msg = {DL_LMB};

    printf("%f, %f, %f\n", ui.position.x, ui.position.y, ui.position.z);

    while (window.running)
    {
        dl_frame_begin();

        dl_poll_events(&window);

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background(vec4(0.1f, 0.1f, 0.1f, 1.0f));
        dl_renderer_clear();

        dl_camera_update();
        dl_ui_entity_update(&ui);

        dl_window_swap_buffer(&window);
        dl_frame_end();

        dl_ui_entity_is_mouse_over(&ui, &window);

        if(dl_ui_entity_is_mouse_over(&ui, &window))
        {
        }
    }
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();
    return 0;
}