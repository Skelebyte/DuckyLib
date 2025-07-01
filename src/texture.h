#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"

typedef enum GLR_Blendmode
{
    GLR_NEAREST,
    GLR_LINEAR
} GLR_Blendmode, Blendmode;

typedef struct GLR_Texture 
{
    unsigned int id;
    const char *path;
} GLR_Texture, Texture;

int glt_texture_load(GLR_Texture *texture, const char *path, GLR_Blendmode blendmode) 
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, blendmode == GLR_LINEAR ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, blendmode == GLR_LINEAR ? GL_LINEAR : GL_NEAREST);

    int width, height, channel_count;

    unsigned char *data = stbi_load(path, &width, &height, &channel_count, 0);
    printf("channels: %d\n", channel_count);
    if (data)
    {
        GLenum format = channel_count == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        // proc gen missing texture
        width = 4;
        height = 4;
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
                    data[index] = 0;
                    data[index + 1] = 0;
                    data[index + 2] = 0;
                } else
                {
                    data[index] = 255;
                    data[index + 1] = 0;
                    data[index + 2] = 255;
                }
            }
        }
        if(!data)
            printf("failed to generate missing texture!\n");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    texture->path = path;

    return 0;
}

int glt_bind_texture(GLR_Texture *texture) 
{
    glBindTexture(GL_TEXTURE_2D, texture->id);

    return 0;
}

#endif