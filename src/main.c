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
    if (glr_window_create(&window, "Under 100 lines of code!!", 800, 800))
    {
        printf("bogus\n");
    }

    glr_enable_transparency(true);
    glr_enable_depth_test(true);
    glr_enable_culling(false);
    glr_enable_multisample(true);

    Entity entity = gle_new_entity(vertices, sizeof(vertices), GLR_VERT_SHADER_DEFAULT, GLR_FRAG_SHADER_DEFAULT);
    entity.position = vec3(0.0f, 0.0f, -1.0f);

    GLR_Texture texture;
    glt_texture_load(&texture, "data/textures/frank.png", GLR_LINEAR);

    glr_unbind_all(&entity.renderer);

    Entity entity2 = gle_new_entity(vertices, sizeof(vertices), GLR_VERT_SHADER_DEFAULT, GLR_FRAG_SHADER_DEFAULT);
    entity2.position = vec3(1.0f, 1.0f, -1.0f);

    GLR_Texture texture2;
    glt_texture_load(&texture2, "data/textures/Circle.png", GLR_LINEAR);

    glr_unbind_all(&entity2.renderer);

    glc_camera(75.0f, GLR_1920x1080, 0.01f, 100.0f);
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

    bool printed = false;

    printf("verts %d\n", glr_number_of_verts);

    while (window.running)
    {
        while (SDL_PollEvent(&window.sdl_event))
        {
            glw_poll_events(&window);
            camera.position.z += gli_get_axis(&window, vertical) / 10.0f;
            camera.position.x += gli_get_axis(&window, horizontal) / 10.0f;
            camera.position.y += gli_get_axis(&window, up_down) / 10.0f;
        }

        entity2.rotation.y = z;

        glw_window_viewport(&window, GLR_1920x1080);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glw_use_program(&entity.renderer);
        glUniform4fv(glGetUniformLocation(entity.renderer.shader_program, "color"), 1, vec4(1.0f, 1.0f, 1.0f, 1.0f).data);
        glw_use_program(&entity2.renderer);
        glUniform4fv(glGetUniformLocation(entity2.renderer.shader_program, "color"), 1, vec4(1.0f, 1.0f, 1.0f, 1.0f).data);

        gle_update(&entity);
        gle_update(&entity2);

        glr_bind_vao(&entity.renderer);
        glt_bind_texture(&texture);
        glr_draw(&entity.renderer);

        glr_bind_vao(&entity2.renderer);
        glt_bind_texture(&texture2);
        glr_draw(&entity2.renderer);

        glr_end_draw();
        glw_window_swap_buffer(&window);

        if(z < 360) {
            z++;
        }
        else
        {
            z = 0;
        }
        glc_camera(75.0f, GLR_1920x1080, 0.01f, 100.0f);

        if(!printed) 
        {
            printed = true;
            printf("%f, %f, %f\n", entity2.position.x, entity2.position.y, entity2.position.z);
        }
    }

    glr_delete_renderer(&entity.renderer);
    glw_window_destroy(&window);
    SDL_Quit();
    return 0;
}