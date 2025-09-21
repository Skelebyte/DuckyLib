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

DL_UIEntity dl_ui_entity_new(const char *texture_dir, DL_Blendmode blendmode, DL_AspectRatios ratio, const char *vert_src_dir, const char *frag_src_dir);
void dl_ui_entity_update(DL_UIEntity *ui_entity);
bool dl_ui_entity_is_mouse_over(DL_UIEntity *ui_entity, DL_Window *window);
void dl_ui_entity_destroy(DL_UIEntity *ui_entity);

#endif
