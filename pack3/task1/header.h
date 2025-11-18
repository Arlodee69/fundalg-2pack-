#pragma once

#include <stdio.h>
#include <string.h>


typedef enum{
    VALID = 0,
    INVALID_INPUT = 1,
}status;

unsigned int sumOne(unsigned int a);
unsigned int subtractOne(unsigned int a);
status convert(const unsigned int number, const int r, char* output);