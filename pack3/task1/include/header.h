#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

typedef enum{
    VALID = 0,
    INVALID_INPUT = 1,
    OVERFLOW_ERROR = 2
}status;

unsigned int sumOne(unsigned int a);
unsigned int subtractOne(unsigned int a);
status convert(const int number, const int r, char* output);

#endif