#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "renderer.h"
#include "file.h"
#include "utils/cmath.h"
#include "texture.h"
#include "input.h"
#include "entity.h"
#include "camera.h"
#include "time.h"

int main(int argc, char *argv[])
{
    // square
    float vertices[] = {
        // First triangle
        // positions        // texture coords
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // top left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        // Second triangle
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
    };

    Window window;
    if (glr_window_create(&window, "not too shabby", 800, 800))
    {
        printf("window failed\n");
    }

    glr_enable_transparency(true);
    glr_enable_depth_test(true);
    glr_enable_culling(false);
    glr_enable_multisample(true);

    Entity entity = gle_new_entity(vertices, sizeof(vertices), GLR_VERT_SHADER_DEFAULT, GLR_FRAG_SHADER_DEFAULT);
    entity.position = vec3(0.0f, 0.0f, -3.5f);

    glm_new_material(&entity.material, "data/textures/frank.png", GL_LINEAR, GLR_WHITE_COLOR);

    glr_unbind_all(&entity.renderer);

    Entity entity2 = gle_new_entity(vertices, sizeof(vertices), GLR_VERT_SHADER_DEFAULT, GLR_FRAG_SHADER_DEFAULT);
    entity2.position = vec3(0.5f, 0.5f, -2.0f);

    glr_unbind_all(&entity2.renderer);

    glc_new_camera(75.0f, GLR_1920x1080, 0.1f, 100.0f);    
    int z = 0;

    InputAxis vertical = {
        GLR_S,
        GLR_W
    };
    InputAxis horizontal = {
        GLR_D,
        GLR_A
    };

    InputAxis up_down = {
        GLR_Q,
        GLR_E
    };

    while (window.running)
    {
        glt_begin_frame();
        while (SDL_PollEvent(&window.sdl_event))
        {
            glw_poll_events(&window);
            camera.position.z += gli_get_axis(&window, vertical) / 10.0f;
            camera.position.x += gli_get_axis(&window, horizontal) / 10.0f;
            camera.position.y += gli_get_axis(&window, up_down) / 10.0f;
        }

        entity2.rotation.y = z;

        glw_window_viewport(&window, GLR_1920x1080);
        glr_background_color((Vec4){0.1f, 0.1f, 0.1f, 1.0f});
        glr_clear();

        gle_update(&entity);
        gle_update(&entity2);

        glw_window_swap_buffer(&window);

        printf("fps: %d\n", time.fps);

        if(z < 360) {
            z++;
        }
        else
        {
            z = 0;
        }
        glc_camera_update();

        glt_end_frame();
    }

    gle_delete_entity(&entity);
    gle_delete_entity(&entity2);
    glw_window_destroy(&window);
    SDL_Quit();
    return 0;
}