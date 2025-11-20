#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

typedef enum{
    VALID = 0,
    INVALID = 1,
    OVERFLOW_ERROR = 2,
    ALLOCATION_ERROR = 3,
    YES = 10,
    NO = -10,
}status_code;

#endif