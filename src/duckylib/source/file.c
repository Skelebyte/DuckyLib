#include "../utils/file.h"

const char *file_read(const char *dir)
{
    FILE *file;
    char *buffer;
    long file_size;
    long bytes_read;

    file = fopen(dir, "rb");

    if (file == NULL)
    {
        printf("Could not open file!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL)
    {
        perror("Failed to allocate memory to buffer!\n");
        fclose(file);
        return NULL;
    }

    bytes_read = fread(buffer, 1, file_size, file);
    if(bytes_read != file_size)
    {
        printf("failed to read :(\n");
        free(buffer);
        fclose(file);
        return NULL;
    } else
    {
        buffer[file_size] = 0;
    }

    fclose(file);



    return buffer;
}
