#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include "glad/glad.h"

typedef struct GLR_Renderer
{
    unsigned int shader_program;

    unsigned int vao;
    unsigned int vbo;
} GLR_Renderer, Renderer;

int glr_compile_shaders(GLR_Renderer *renderer, const char *v_shader_src, const char *f_shader_src)
{
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &v_shader_src, NULL);
    glCompileShader(vertex_shader);

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_shader_src, NULL);
    glCompileShader(fragment_shader);

    renderer->shader_program = glCreateProgram();

    glAttachShader(renderer->shader_program, vertex_shader);
    glAttachShader(renderer->shader_program, fragment_shader);

    glLinkProgram(renderer->shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return 0;
}

int glr_gen_vert_objs(GLR_Renderer *renderer, void *data)
{
    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);

    glBindVertexArray(renderer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 0;
}

int glr_use_program(GLR_Renderer *renderer)
{
    glUseProgram(renderer->shader_program);

    return 0;
}

int glr_bind_vert_arr(GLR_Renderer *renderer)
{
    glBindVertexArray(renderer->vao);

    return 0;
}

int glr_draw(GLR_Renderer *renderer)
{
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return 0;
}

int glr_delete_renderer(GLR_Renderer *renderer)
{
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);

    glDeleteProgram(renderer->shader_program);

    return 0;
}

#endif