#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

char digit_to_char(int digit);
char digit_to_char_upper(int digit);
int char_to_digit(char c);
void convert_to_base(char *buffer, long long num, int base, int upper);
long long convert_from_base(const char *str, int base);
void int_to_roman(char *buffer, int num);
#define MAX_FIB 46
void generate_fib();
void zeckendorf(unsigned int num, char *buffer);
void print_memory_dump(void *ptr, size_t size, char *buffer);
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

#endif