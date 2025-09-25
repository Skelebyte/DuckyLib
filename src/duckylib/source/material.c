#include "../material.h"

int dl_material_new(DL_Material *material, const char *texture_path, DL_Blendmode blendmode, Vec4 color, bool path_is_data)
{
    if(!path_is_data)
    {
        dl_texture_load(&material->texture, texture_path, blendmode);
    }
    // else
    // {
    //     dl_texture_data_load(&material->texture, texture_path, blendmode);
    // }
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
