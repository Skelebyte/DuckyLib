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

DL_Entity dl_entity_new(float *data, size_t size, const char *vert_src_dir, const char *frag_src_dir);

void dl_entity_update(DL_Entity *entity);

void dl_entity_destroy(DL_Entity *entity);
#endif
