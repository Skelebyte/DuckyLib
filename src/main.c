#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "renderer.h"
#include "file.h"

int main(void *)
{

    float vertices[] = {
        -0.5f, -0.5f * sqrt(3) / 3, 0.0f, // top
        0.5f, -0.5f * sqrt(3) / 3, 0.0f,  // left
        0.0f, 0.5f, sqrt(3) * 2 / 3, 0.0f // right
    };
    Window *window;

    if (glr_window_create(window, "OGLR Renderer", 800, 800))
    {
        printf("bogus\n");
    }

    glViewport(0, 0, 800, 800);

    Renderer renderer = {0};

    glr_compile_shaders(&renderer, read_file("data/shaders/vertex.glsl"), read_file("data/shaders/fragment.glsl"));

    glr_gen_vert_objs(&renderer, (void *)vertices);

    while (!glr_window_should_close(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glr_use_program(&renderer);
        glr_bind_vert_arr(&renderer);
        glr_draw(&renderer);
        glr_window_swap_buffer(window);
    }

    glr_delete_renderer(&renderer);
    glr_window_destroy(window);
    SDL_Quit();
    return 0;
}