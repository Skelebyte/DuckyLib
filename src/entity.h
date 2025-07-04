#ifndef ENTITY_H
#define ENTITY_H

#include "utils/vec3.h"
#include "utils/vec4.h"
#include "utils/mat4.h"
#include "renderer.h"
#include "file.h"
#include "material.h"

typedef struct GLR_Entity
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    Mat4 model;
    GLR_Material material;

    GLR_Renderer renderer;

} GLR_Entity, Entity;

GLR_Entity gle_new_entity(float *data, size_t size, const char *vert_src_dir, const char *frag_src_dir)
{
    GLR_Entity entity = {
        vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, 0.0f),
        vec3(1.0f, 1.0f, 1.0f),
        mat4_identity(),
        {0}
    };
    entity.model = mat4_custom(entity.position, entity.rotation, entity.scale);
    glr_compile_shaders(&entity.renderer, read_file(vert_src_dir), read_file(frag_src_dir));
    glr_get_opengl_error("shader comp", __LINE__);

    glr_gen_vao(&entity.renderer);
    glr_get_opengl_error("vbo", __LINE__);
    glr_gen_vbo(&entity.renderer, data, size);
    glr_get_opengl_error("vbo", __LINE__);

    glr_vao_link_attrib(&entity.renderer, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);                   // vertex position
    glr_get_opengl_error("vertex position", __LINE__);
    glr_vao_link_attrib(&entity.renderer, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float))); // texture coordinate
    glr_get_opengl_error("texture coords", __LINE__);

    glm_new_material(&entity.material, GLR_DEFAULT_TEXTURE, GLR_NEAREST, GLR_WHITE_COLOR);
    glr_get_opengl_error("new material", __LINE__);

    return entity;
}

int gle_update(GLR_Entity *entity) 
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

    entity->model = mat4_custom(entity->position, entity->rotation, entity->scale);

    glw_use_program(&entity->renderer);

    glUniformMatrix4fv(glGetUniformLocation(entity->renderer.shader_program, "model"), 1, GL_FALSE, entity->model);

    

    glm_activate_material(&entity->material, &entity->renderer);

    glr_bind_vao(&entity->renderer);
    glt_bind_texture(&entity->material.texture);
    glr_draw(&entity->renderer);

    return 0;
}

int gle_delete_entity(GLR_Entity *entity)
{
    mat4_free(entity->model);
    glr_delete_renderer(&entity->renderer);
}

#endif