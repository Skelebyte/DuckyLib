#ifndef ENTITY_H
#define ENTITY_H

#include "utils/vec3.h"
#include "utils/vec4.h"
#include "utils/mat4.h"
#include "renderer.h"
#include "utils/file.h"
#include "material.h"
#include "constants.h"

typedef struct DL_Entity
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    Mat4 model;
    DL_Material material;

    DL_Renderer renderer;

} DL_Entity, Entity;

DL_Entity dl_entity_new(float *data, size_t size, const char *vert_src_dir, const char *frag_src_dir)
{
    DL_Entity entity = {
        vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, 0.0f),
        vec3(1.0f, 1.0f, 1.0f),
    };
    mat4_custom(entity.model, entity.position, entity.rotation, entity.scale);

    if(vert_src_dir == NULL)
    {
        vert_src_dir = dl_vert_shader;   
    } else 
    {
        vert_src_dir = read_file(vert_src_dir);
    }
    if(frag_src_dir == NULL)
    {
        frag_src_dir = dl_frag_shader;
    } else
    {
        frag_src_dir = read_file(frag_src_dir);
    }

    dl_renderer_compile_shaders(&entity.renderer, vert_src_dir, frag_src_dir);

    dl_renderer_opengl_error("shader comp", __LINE__);

    dl_renderer_gen_vao(&entity.renderer);
    dl_renderer_opengl_error("vbo", __LINE__);
    dl_renderer_gen_vbo(&entity.renderer, data, size);
    dl_renderer_opengl_error("vbo", __LINE__);

    dl_renderer_link_attrib(&entity.renderer, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);                   // vertex position
    dl_renderer_opengl_error("vertex position", __LINE__);
    dl_renderer_link_attrib(&entity.renderer, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float))); // texture coordinate
    dl_renderer_opengl_error("texture coords", __LINE__);

    dl_material_new(&entity.material, DL_DEFAULT_TEXTURE, BM_NEAREST, DL_WHITE);
    dl_renderer_opengl_error("new material", __LINE__);

    return entity;
}

void dl_entity_update(DL_Entity *entity) 
{

    if(entity->rotation.x > 360) 
    {
        entity->rotation.x = entity->rotation.x - 360;
    }
    else if (entity->rotation.x < 0) 
    {
        entity->rotation.x = entity->rotation.x + 360;
    }

    if (entity->rotation.y > 360)
    {
        entity->rotation.y = entity->rotation.y - 360;
    }
    else if (entity->rotation.y < 0)
    {
        entity->rotation.y = entity->rotation.y + 360;
    }

    if (entity->rotation.z > 360)
    {
        entity->rotation.z = entity->rotation.z - 360;
    }
    else if (entity->rotation.z < 0)
    {
        entity->rotation.z = entity->rotation.z + 360;
    }

    
    mat4_custom(entity->model, entity->position, entity->rotation, entity->scale);

    dl_renderer_use_program(&entity->renderer);

    glUniformMatrix4fv(glGetUniformLocation(entity->renderer.shader_program, "model"), 1, GL_FALSE, entity->model);

    

    dl_material_activate(&entity->material, &entity->renderer);

    dl_renderer_bind_vao(&entity->renderer);
    dl_texture_bind(&entity->material.texture);
    dl_renderer_draw(&entity->renderer);
}

void dl_entity_destroy(DL_Entity *entity)
{
    dl_renderer_delete(&entity->renderer);
}

#endif