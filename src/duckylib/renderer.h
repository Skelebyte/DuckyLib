#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include "glad/glad.h"
#include "camera.h"

typedef struct DL_Renderer
{
    unsigned int shader_program;

    unsigned int vao;
    unsigned int vbo;

    unsigned int vertex_count;
} DL_Renderer, Renderer;

int dl_renderer_opengl_error(const char *file, int line);
int dl_renderer_enable_transparency(bool toggle);
int dl_renderer_enable_depth_test(bool toggle);
int dl_renderer_enable_culling(bool toggle);
int dl_renderer_enable_antialiasing(bool toggle);
int dl_renderer_set_background(Vec4 color);
int dl_renderer_clear();
int dl_renderer_compile_shaders(DL_Renderer *renderer, const char *v_shader_src, const char *f_shader_src);
int dl_renderer_unbind_vao(DL_Renderer *renderer);
int dl_renderer_unbind_vbo(DL_Renderer *renderer);
int dl_renderer_unbind_all(DL_Renderer *renderer);
int dl_renderer_gen_vao(DL_Renderer *renderer);
int dl_renderer_gen_vbo(DL_Renderer *renderer, float *data, size_t size);
int dl_renderer_link_attrib(DL_Renderer *renderer, unsigned int layout, unsigned int amount, GLenum type, GLsizeiptr stride, void* offset);
int dl_renderer_use_program(DL_Renderer *renderer);
int dl_renderer_bind_vao(DL_Renderer *renderer);
int dl_renderer_draw(DL_Renderer *renderer);
int dl_renderer_delete(DL_Renderer *renderer);

#endif
