#include <stdio.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, "DuckyLib", true, true);

    DL_UIEntity ui = dl_ui_entity_new(NULL, BM_NEAREST, DL_Aspect_1920x1080, NULL, NULL);
    // ui.scale.y = 0.5f;
    dl_renderer_unbind_all(&ui.renderer);

    DL_UIEntity ui2 = dl_ui_entity_new(DL_DEFAULT_TEXTURE, BM_NEAREST, DL_Aspect_1920x1080, NULL, NULL);
    ui2.scale.x = 10.0f;
    ui2.scale.y = 10.0f;
    dl_renderer_unbind_all(&ui2.renderer);

    printf("%f\n", ui.aspect_ratio);

    DL_Bind lmb = {DL_LMB};
    DL_Bind spc = {DL_SPACE};

    while (window.running)
    {
        dl_frame_begin();

        dl_poll_events(&window);

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background(vec4(0.1f, 0.1f, 0.1f, 1.0f));
        dl_renderer_clear();

        dl_camera_update();
        dl_ui_entity_update(&ui);
        dl_ui_entity_update(&ui2);

        // if(dl_ui_entity_is_mouse_over(&ui, &window))
        // {

        // }

        if(dl_input_get_key_down(&spc, true))
        {
            dl_log_new("yo", DL_MSG);
        }

        if (dl_input_get_key_down(&lmb, false))
        {
            // float x = dl_input_get_mouse_position().x;
            // x -= window.viewport_x;
            // x -= window.viewport_w / 2;
            // x /= window.viewport_w / 2;
            // float y = dl_input_get_mouse_position().y;
            // y -= window.viewport_y;
            // y -= window.viewport_h / 2;
            // y /= window.viewport_h / 2;
            // ui.position.x = x;
            // ui.position.y = -y;

            ui.position = dl_input_get_mouse_position(&window);
        }

        dl_window_swap_buffer(&window);
        dl_frame_end();
    }
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();


    return 0;
}
