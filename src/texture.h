#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"

typedef enum GLR_ImageFormat 
{
    GLR_PNG,
    GLR_JPG
} GLR_ImageFormat, ImageFormat;

typedef struct GLR_Texture 
{
    unsigned int id;
    const char *path;
    GLR_ImageFormat image_format;
} GLR_Texture, Texture;

int glt_texture_load(GLR_Texture *texture, const char *path, GLR_ImageFormat format) 
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channel_count;

    unsigned char *data = stbi_load(path, &width, &height, &channel_count, 0);
    printf("channels: %d\n", channel_count);
    if (data)
    {
        if(format == GLR_PNG) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("loser\n");
    }

    stbi_image_free(data);

    texture->path = path;
    texture->image_format = format;
    
    return 0;
}

int glt_bind_texture(GLR_Texture *texture) 
{
    glBindTexture(GL_TEXTURE_2D, texture->id);

    return 0;
}

#endif