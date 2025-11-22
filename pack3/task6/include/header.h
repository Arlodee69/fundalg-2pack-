#ifndef HEADER_H
#define HEADER_H

#include "stack.h"
#include <string.h>
#include <limits.h>

typedef enum{
    CORRECT = 1,
    INCORRECT = 0,
    UNDEFINE = -1,
}status;

status check_brackets(const char *str);
bool is_open_skobka(char c);
bool is_close_skobka(char c);
bool matches(char open, char close);

#endif