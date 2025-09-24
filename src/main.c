#include <stdio.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, "DuckyLib", true, true);

    DL_UIEntity ui = dl_ui_entity_new("data/textures/Circle.png", BM_LINEAR, DL_Aspect_1920x1080, NULL, NULL);
    //ui.material.color.w = 0.5f;
    dl_renderer_unbind_all(&ui.renderer);

    DL_Entity object = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    object.position.z = -10;
    dl_renderer_unbind_all(&object.renderer);

    DL_Entity object2 = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);

    dl_texture_load(&object2.material.texture, "data/textures/Circle.png", BM_LINEAR);
    object2.position.z = -8;
    object2.position.x = 0.5f;
    dl_renderer_unbind_all(&object2.renderer);

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

        dl_entity_update(&object);
        dl_entity_update(&object2);

        if(dl_input_get_key_down(&spc, true))
        {
            object.position.z += 1;
        }

        if (dl_input_get_key_down(&lmb, false))
        {
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
