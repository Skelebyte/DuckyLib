#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb/stb_image.h"
#include "glad/glad.h"

#define DL_MISSING_TEXTURE "DL_MISSING_TEXTURE"
#define DL_SOLID_TEXTURE "DL_SOLID_TEXTURE"
#define DL_DEFAULT_TEXTURE "DL_DEFAULT_TEXTURE"

typedef enum DL_Blendmode
{
    BM_NEAREST,
    BM_LINEAR
} DL_Blendmode, Blendmode;

typedef struct DL_Texture
{
    unsigned int id;
    const char *path;
} DL_Texture, Texture;

unsigned char *dl_texture_generate(int width, int height, int r1, int g1, int b1, int r2, int g2, int b2);
int dl_texture_load(DL_Texture *texture, const char *path, DL_Blendmode blendmode);
int dl_texture_bind(Texture *texture);



#endif
