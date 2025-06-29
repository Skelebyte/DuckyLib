#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "renderer.h"
#include "file.h"
#include "utils/cmath.h"
#include "texture.h"

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
        // positions        // texture coords
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        // Second triangle
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
    };

    Window window;
    if (glr_window_create(&window, "Under 100 lines of code!!", 800, 800))
    {
        printf("bogus\n");
    }

    glViewport(0, 0, 800, 800);

    Renderer renderer = {0};

    glr_enable_transparency();
    glr_enable_depth_test();
    glr_enable_culling();

    glr_compile_shaders(&renderer, read_file("data/shaders/vertex.glsl"), read_file("data/shaders/fragment.glsl"));

    glr_gen_vao(&renderer);
    glr_gen_vbo(&renderer, vertices, 30);

    glr_vao_link_attrib(&renderer, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
    glr_vao_link_attrib(&renderer, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    GLR_Texture texture;
    glt_texture_load(&texture, "data/textures/missing_texture.png", GLR_PNG);

    glr_unbind_all(&renderer);

    Mat4 projection = cmath_perspective(cmath_to_radians(60), glr_get_virtual_aspect(GLR_1280x720), 0.1f, 100.0f);

    Vec3 camera_pos = vec3(0.0f, 0.0f, 10.0f);
    Mat4 view = mat4_look_at(camera_pos, vec3_add(camera_pos, vec3(0.0f, 0.0f, -1.0f)));

    Mat4 camera_matrix = mat4_multiply(projection, view);
    int z = 0;
    Mat4 model = mat4_custom(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));

    float dist = 0.0f;

    while (!glw_window_should_close(&window))
    {

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glw_window_viewport(&window, GLR_1280x720);

        glw_use_program(&renderer);
        glUniformMatrix4fv(glGetUniformLocation(renderer.shader_program, "camera_matrix"), 1, GL_TRUE, &camera_matrix.matrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(renderer.shader_program, "model"), 1, GL_TRUE, &model.matrix[0][0]);

        glr_bind_vao(&renderer);

        glt_bind_texture(&texture);
        glr_draw(&renderer);

        glw_window_swap_buffer(&window);

        if(z < 360) {
            z++;
        }
        else
        {
            z = 0;
        }

         camera_pos.z -= 0.01f;
        // camera_pos.x += 0.01f;
        // camera_pos.y += 0.01f;
        //printf("%f\n", camera_pos.z);
         view = mat4_look_at(camera_pos, vec3_add(vec3(0, 0, -1), camera_pos));

         camera_matrix = mat4_multiply(projection, view);

         model = mat4_custom(vec3(0, 0, 0), vec3(z, z, z), vec3(0.1f, 0.1f, 0.1f));
        
    }

    glr_delete_renderer(&renderer);
    glw_window_destroy(&window);
    SDL_Quit();
    return 0;
}