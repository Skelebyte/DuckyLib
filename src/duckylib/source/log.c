#include "../utils/log.h"

char *dl_log_dir = "data/logs/duckylib.log";

int dl_log_new(char *content, DL_LogLevel log_level)
{

    if(strlen(content) > DL_LOG_MAX_LEN)
    {
        printf("dl_log_new (log.h): content is %d, and DL_LOG_MAX_LEN is %d. Please edit DL_LOG_MAX_LEN in log.h, or change you log message.\n", strlen(content), DL_LOG_MAX_LEN);
        return 2;
    }

    FILE *file;

    file = fopen(dl_log_dir, "a");

    if(file == NULL)
    {
        printf("file is NULL\n");
        return 1;
    }

    if(log_level == DL_MSG)
    {
        char log_content[DL_LOG_MAX_LEN + 8] = "MSG : ";
        strcat(log_content, content);
        strcat(log_content, "\n");
        fprintf(file, log_content);
    }
    if (log_level == DL_WRN)
    {
        char log_content[DL_LOG_MAX_LEN + 8] = "WRN : ";
        strcat(log_content, content);
        strcat(log_content, "\n");
        fprintf(file, log_content);
    }
    if (log_level == DL_ERR)
    {
        char log_content[DL_LOG_MAX_LEN + 8] = "ERR : ";
        strcat(log_content, content);
        strcat(log_content, "\n");
        fprintf(file, log_content);
    }

    fclose(file);

    return 0;
}