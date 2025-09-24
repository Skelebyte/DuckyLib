#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>

#define DL_LOG_MAX_LEN 50

typedef enum DL_LogLevel
{
    DL_MSG = 0,
    DL_WRN = 1,
    DL_ERR = 2
} DL_LogLevel, LogLevel;

extern char *dl_log_dir;

int dl_log_new(char *content, DL_LogLevel log_level);

#endif