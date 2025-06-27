#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#define FILE_LINE_BUFFER_MAX 256

const char *read_file(const char *dir)
{
    FILE *file;
    char buffer[FILE_LINE_BUFFER_MAX];
    const char *content;

    file = fopen(dir, "r");

    if (file == NULL)
    {
        printf("Could not open file!\n");
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
    }

    content = buffer;

    fclose(file);

    return content;
}

#endif