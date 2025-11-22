#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    char *data;
    size_t count;
    size_t capacity;
}Stack;

Stack *create(Stack *stack, size_t cap);
void destroy(Stack *stack);
bool is_empty(Stack *stack);
bool is_full(Stack *stack);
Stack *push(Stack *stack, char data);
char pop(Stack *stack);
char top(Stack *stack);
size_t get_size(Stack *stack);

#endif