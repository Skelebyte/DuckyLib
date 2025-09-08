#ifndef UI_ENTITY_H
#define UI_ENTITY_H

#include "utils/vec3.h"
#include "utils/vec4.h"
#include "utils/mat4.h"
#include "renderer.h"
#include "utils/file.h"
#include "texture.h"
#include "constants.h"
#include "material.h"
#include "input.h"

typedef struct DL_UIEntity 
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    Mat4 model;

    DL_Material material;

    DL_Renderer renderer;

    float aspect_ratio;
    bool allow_out_of_bounds;

} DL_UIEntity, UIEntity;

DL_UIEntity dl_ui_entity_new(const char *texture_dir, DL_Blendmode blendmode, DL_AspectRatios ratio, const char *vert_src_dir, const char *frag_src_dir)
{
    DL_UIEntity ui_entity = {
        vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, 0.0f),
        vec3(1.0f, 1.0f, 1.0f),
    };
    ui_entity.aspect_ratio = dl_get_virtual_aspect(ratio);
    mat4_custom(ui_entity.model, ui_entity.position, ui_entity.rotation, ui_entity.scale, Mat4_TSR);

    if (vert_src_dir == NULL)
    {
        vert_src_dir = dl_ui_vert_shader;
    }
    else
    {
        vert_src_dir = file_read(vert_src_dir);
    }

    if (frag_src_dir == NULL)
    {
        frag_src_dir = dl_ui_frag_shader;
    }
    else
    {
        frag_src_dir = file_read(frag_src_dir);
    }

    dl_renderer_compile_shaders(&ui_entity.renderer, vert_src_dir, frag_src_dir);
    dl_renderer_opengl_error("DL_UIEntity shader compilation failed!", __LINE__);

    dl_renderer_gen_vao(&ui_entity.renderer);
    dl_renderer_opengl_error("DL_UIEntity VAO generation failed!", __LINE__);
    dl_renderer_gen_vbo(&ui_entity.renderer, dl_square_2d, sizeof(dl_square_2d));
    dl_renderer_opengl_error("DL_UIEntity VBO generation failed!", __LINE__);

    dl_renderer_link_attrib(&ui_entity.renderer, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0); // vertex position
    dl_renderer_opengl_error("DL_UIEntity vertex position link failed!", __LINE__);
    dl_renderer_link_attrib(&ui_entity.renderer, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float))); // texture coordinate
    dl_renderer_opengl_error("DL_UIEntity texture coord link failed!", __LINE__);


    if(texture_dir == NULL)
    {
        texture_dir = DL_DEFAULT_TEXTURE;
    }

    dl_material_new(&ui_entity.material, texture_dir, blendmode, DL_WHITE);

    return ui_entity;
}

void dl_ui_entity_update(DL_UIEntity *ui_entity)
{
    if (ui_entity->rotation.x > 360)
    {
        ui_entity->rotation.x = ui_entity->rotation.x - 360;
    }
    else if (ui_entity->rotation.x < 0)
    {
        ui_entity->rotation.x = ui_entity->rotation.x + 360;
    }

    if (ui_entity->rotation.y > 360)
    {
        ui_entity->rotation.y = ui_entity->rotation.y - 360;
    }
    else if (ui_entity->rotation.y < 0)
    {
        ui_entity->rotation.y = ui_entity->rotation.y + 360;
    }

    if (ui_entity->rotation.z > 360)
    {
        ui_entity->rotation.z = ui_entity->rotation.z - 360;
    }
    else if (ui_entity->rotation.z < 0)
    {
        ui_entity->rotation.z = ui_entity->rotation.z + 360;
    }

    if(ui_entity->allow_out_of_bounds == false)
    {
        if (ui_entity->position.x > 1.0f)
        {
            ui_entity->position.x = 1.0f;
        }
        if (ui_entity->position.x < -1.0f)
        {
            ui_entity->position.x = -1.0f;
        }

        if (ui_entity->position.y > 1.0f)
        {
            ui_entity->position.y = 1.0f;
        }
        if (ui_entity->position.y < -1.0f)
        {
            ui_entity->position.y = -1.0f;
        }
    }

    mat4_custom(ui_entity->model, ui_entity->position, ui_entity->rotation, vec3(ui_entity->scale.x, ui_entity->scale.y * ui_entity->aspect_ratio, ui_entity->scale.z), Mat4_TSR);

    dl_renderer_use_program(&ui_entity->renderer);

    glUniformMatrix4fv(glGetUniformLocation(ui_entity->renderer.shader_program, "model"), 1, GL_FALSE, ui_entity->model);


    dl_renderer_bind_vao(&ui_entity->renderer);
    dl_material_activate(&ui_entity->material, &ui_entity->renderer);
    dl_renderer_draw(&ui_entity->renderer);
}

bool dl_ui_entity_is_mouse_over(DL_UIEntity *ui_entity, DL_Window *window)
{
    dl_renderer_enable_transparency(false);

    Vec2 mouse_position = dl_input_get_mouse_position();
    mouse_position.x -= window->viewport_w;
    mouse_position.y = window->viewport_h - (mouse_position.y - window->viewport_y) - 1;

    DL_Texture texture;
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, window->viewport_w, window->viewport_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    unsigned int frame_buffer;
    glGenFramebuffers(1, &frame_buffer);

    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        dl_renderer_opengl_error("dl_ui_entity_is_mouse_over", 0);
        glDeleteFramebuffers(1, &frame_buffer);
        return false;
    } 

    dl_renderer_set_background(vec4(0.0f, 0.0f, 0.0f, 0.0f));
    dl_renderer_clear();
    glViewport(0, 0, window->viewport_w, window->viewport_h);
    dl_ui_entity_update(ui_entity);

    char data[4];

    glReadPixels(mouse_position.x, mouse_position.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
    dl_renderer_enable_transparency(true);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteTextures(1, &texture.id);
    glDeleteFramebuffers(1, &frame_buffer);
    if (data[3] != 0)
    {
        printf("%d\n", data[3]);
        return true;
    } 
    else 
    {
        printf("ahahaah\n");
        return false;
    }
}

void dl_ui_entity_destroy(DL_UIEntity *ui_entity)
{

    dl_renderer_delete(&ui_entity->renderer);
}

#endif