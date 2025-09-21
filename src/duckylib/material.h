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

int dl_material_new(DL_Material *material, const char *texture_path, DL_Blendmode blendmode, Vec4 color);

int dl_material_activate(DL_Material *material, DL_Renderer *renderer);

#endif
