#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "renderer.h"
#include "utils/vec4.h"

#define GLR_WHITE_COLOR (Vec4){1.0f, 1.0f, 1.0f, 1.0f}

typedef struct GLR_Material
{
    GLR_Texture texture;
    Vec4 color;
} GLR_Material, Material;

int glm_new_material(GLR_Material *material, const char *texture_path, GLR_Blendmode blendmode, Vec4 color)
{
    glt_texture_load(&material->texture, texture_path, blendmode);
    material->color = color;

    return 0;
}

int glm_activate_material(GLR_Material *material, GLR_Renderer *renderer)
{
    glUniform4fv(glGetUniformLocation(renderer->shader_program, "color"), 1, material->color.data);
    glr_get_opengl_error("color", __LINE__);
    return 0;
}

#endif