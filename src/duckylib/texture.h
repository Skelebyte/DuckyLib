#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"

#define DL_DEFAULT_TEXTURE "DL_DEFAULT_TEXTURE"
#define DL_DEFAULT_TEXTURE_SOLID "DL_DEFAULT_TEXTURE_SOLID"

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

unsigned char *dl_texture_generate(int width, int height, int r1, int g1, int b1, int r2, int g2, int b2)
{
    unsigned char *data = (unsigned char *)malloc(width * height * 3);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float t = (float)x / width;
            float s = (float)y / height;

            int index = (y * width + x) * 3;
            if (((int)(s * height) + (int)(t * width)) % 2 == 0)
            {
                data[index] = r1;
                data[index + 1] = g1;
                data[index + 2] = b1;
            }
            else
            {
                data[index] = r2;
                data[index + 1] = g2;
                data[index + 2] = b2;
            }
        }
    }

    return data;
}

int dl_texture_load(DL_Texture *texture, const char *path, DL_Blendmode blendmode) 
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(path != DL_DEFAULT_TEXTURE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, blendmode == BM_LINEAR ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, blendmode == BM_LINEAR ? GL_LINEAR : GL_NEAREST);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    int width, height, channel_count;
    unsigned char *data;

    if (path != DL_DEFAULT_TEXTURE && path != DL_DEFAULT_TEXTURE_SOLID)
    {
        data = stbi_load(path, &width, &height, &channel_count, 0);
    }
    else
    {
        width = 4;
        height = 4;
        if (path == DL_DEFAULT_TEXTURE)
        {
            // proc gen default texture
            data = dl_texture_generate(width, height, 220, 220, 220, 255, 255, 255);
            if (!data)
                printf("failed to generate missing texture!\n");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            free(data);
            return 0;
        }
        if (path == DL_DEFAULT_TEXTURE_SOLID)
        {
            width = 1;
            height = 1;
            // proc gen default texture solid
            data = dl_texture_generate(width, height, 255, 255, 255, 255, 255, 255);
            if (!data)
                printf("failed to generate missing texture!\n");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            free(data);
            return 0;
        }
    }
    if (data)
    {
        GLenum format = channel_count == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        // proc gen missing texture
        width = 4;
        height = 4;
        data = dl_texture_generate(width, height, 255, 0, 255, 0, 0, 0);
        if (!data)
            printf("failed to generate missing texture!\n");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        free(data);
        return 0;
    }

    stbi_image_free(data);

    texture->path = path;

    return 0;
}

int dl_texture_bind(Texture *texture) 
{
    glBindTexture(GL_TEXTURE_2D, texture->id);

    return 0;
}



#endif