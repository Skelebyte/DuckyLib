#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "renderer.h"
#include "utils/vec4.h"

#define DL_WHITE (Vec4){1.0f, 1.0f, 1.0f, 1.0f}

typedef struct DL_Material
{
    DL_Texture texture;
    Vec4 color;
} DL_Material, Material;

int dl_material_new(DL_Material *material, const char *texture_path, DL_Blendmode blendmode, Vec4 color)
{
    dl_texture_load(&material->texture, texture_path, blendmode);
    material->color = color;

    return 0;
}

int dl_material_activate(DL_Material *material, DL_Renderer *renderer)
{
    glUniform4fv(glGetUniformLocation(renderer->shader_program, "color"), 1, material->color.data);
    dl_renderer_opengl_error("dl_material_activate", 0);
    dl_texture_bind(&material->texture);
    return 0;
}

#endif