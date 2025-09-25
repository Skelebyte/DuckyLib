#include <stdio.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, "DuckyLib", true, true);


    while (window.running)
    {
        dl_frame_begin();

        dl_poll_events(&window);

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background(vec4(0.1f, 0.1f, 0.1f, 1.0f));
        dl_renderer_clear();

        dl_camera_update();

        dl_window_swap_buffer(&window);
        dl_frame_end();
    }
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();


    return 0;
}
