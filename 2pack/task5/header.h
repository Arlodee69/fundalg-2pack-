#ifndef HEADER_H
#define HEADER_H

#define MAX_SIZE 256

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef enum{
    ALLOCATION_ERROR = 2,
    FILE_ERROR = 1,
    ARG_ERROR = -1,
    VALID = 0,

}status_code;

status_code parse_file(const char *file_in, const char *file_out);
status_code some_line(FILE *file_out, const char *line);
status_code parse_line(const char *line, char*** words, size_t* count);
char *build_line(char **words, size_t start, size_t end);
void my_free(char **dynamic, size_t count);

#endif