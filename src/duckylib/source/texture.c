#define STB_IMAGE_IMPLEMENTATION
#include "../texture.h"

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

    if (strcmp(path, DL_MISSING_TEXTURE) != 0 && strcmp(path, DL_DEFAULT_TEXTURE) != 0 && strcmp(path, DL_SOLID_TEXTURE) != 0)
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
    if (strcmp(path, DL_MISSING_TEXTURE) != 0 && strcmp(path, DL_DEFAULT_TEXTURE) != 0 && strcmp(path, DL_SOLID_TEXTURE) != 0)
    {
        data = stbi_load(path, &width, &height, &channel_count, 0);
    }
    else
    {
        width = 4;
        height = 4;
        if (strcmp(path, DL_MISSING_TEXTURE) == 0)
        {
            // gen missing texture
            dl_log_new("generating missing texture", DL_MSG);
            data = dl_texture_generate(width, height, 255, 0, 255, 0, 0, 0);
            if (!data)
                printf("failed to generate missing texture!\n");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            free(data);
            return 0;
        }
        if (strcmp(path, DL_SOLID_TEXTURE) == 0)
        {
            width = 1;
            height = 1;
            // gen solid texture
            dl_log_new("generating solid texture", DL_MSG);
            data = dl_texture_generate(width, height, 255, 255, 255, 255, 255, 255);
            if (!data)
                printf("failed to generate solid texture!\n");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            free(data);
            return 0;
        }
        if (strcmp(path, DL_DEFAULT_TEXTURE) == 0)
        {
            // gen default checkered texture
            dl_log_new("generating default texture", DL_MSG);
            data = dl_texture_generate(width, height, 220, 220, 220, 255, 255, 255);
            if (!data)
                printf("failed to generate default checkered texture!\n");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            free(data);
            return 0;
        }
        printf("end\n");
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

        const size_t len1 = strlen("Could not find file: ");
        const size_t len2 = strlen(path);
        const size_t total_len = len1 + len2 + 1;

        char *log_data = malloc(total_len);
        if (!log_data)
        {
            dl_log_new("Failed to malloc error string! (texture.c, dl_texture_load).", DL_ERR);
            return 0;
        }

        memcpy(log_data, "Could not find file: ", len1);
        memcpy(log_data + len1, path, len2 + 1);

        dl_log_new(log_data, DL_ERR);

        free(log_data);
        return 0;
    }

    

    texture->path = path;

    stbi_image_free(data);

    return 0;
}

int dl_texture_data_load(DL_Texture *texture, unsigned char *data, int width, int height, DL_Blendmode blendmode) 
{
    if(texture == NULL || data == NULL)
        return 1;

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, blendmode == BM_LINEAR ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, blendmode == BM_LINEAR ? GL_LINEAR : GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return 0;
}

int dl_texture_bind(Texture *texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->id);

    return 0;
}
