#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "renderer.h"
#include "file.h"
#include "utils/cmath.h"

int main(int argc, char *argv[])
{

    // triangle
    // float vertices[] = {
    //     0.0f, 0.5f * sqrt(3) * 2 / 3, 0.0f, // top
    //     -0.5f, -0.5f * sqrt(3) / 3, 0.0f,   // left
    //     0.5f, -0.5f * sqrt(3) / 3, 0.0f     // right
    // };

    // square
    float vertices[] = {
        // First triangle
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,

        // Second triangle
        -0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
    };


    Window window;
    if (glr_window_create(&window, "OGLR Renderer", 800, 800))
    {
        printf("bogus\n");
    }

    glViewport(0, 0, 800, 800);

    Renderer renderer = {0};

    glr_enable_transparency();
    glr_enable_depth_test();
    glad_glEnable(GL_CULL_FACE);
    glad_glCullFace(GL_FRONT);
    glad_glFrontFace(GL_CCW);

    glr_compile_shaders(&renderer, read_file("data/shaders/vertex.glsl"), read_file("data/shaders/fragment.glsl"));

    glr_gen_vert_objs(&renderer, vertices, 18);

    Mat4 projection = cmath_perspective(cmath_to_radians(60), glr_get_virtual_aspect(GLR_1280x720), 0.1f, 100.0f);

    Vec3 pos = vec3(0.0f, 0.0f, -1.0f);
    Mat4 view = mat4_look_at(pos, vec3_add(pos, vec3(0.0f, 0.0f, 1.0f)));

    Mat4 camera_matrix = mat4_multiply(projection, view);
    int z = 0;
    float far = 0.0f;
    float high = 0.0f;
    Mat4 model = mat4_custom(vec3(0.0f, 0.0f, far), vec3(0.0f, 0.0f, 0.0f), vec3(.1f, .1f, .1f));



    while (!glr_window_should_close(&window))
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glr_window_viewport(&window, GLR_1280x720);



        glr_use_program(&renderer);
        glUniformMatrix4fv(glGetUniformLocation(renderer.shader_program, "camera_matrix"), 1, GL_TRUE, &camera_matrix.matrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(renderer.shader_program, "model"), 1, GL_TRUE, &model.matrix[0][0]);

        glr_bind_vert_arr(&renderer);

        glr_draw(&renderer);



        glr_window_swap_buffer(&window);

        if(z < 360) {
            z++;
        }
        else
        {
            z = 0;
        }

        view = mat4_look_at(pos, vec3_add(pos, vec3(0.0f, 0, 1)));
        camera_matrix = mat4_multiply(projection, view);

        model = mat4_custom(vec3(0, 0, 0), vec3(0, z, 0), vec3(.1f, .1f, .1f));
        
    }

    glr_delete_renderer(&renderer);
    glr_window_destroy(&window);
    SDL_Quit();
    return 0;
}