#include "stack.h"

Stack *create(Stack *stack, size_t cap){
    if(!(stack->data = malloc(sizeof(char) * cap))){
        return NULL;
    }
    stack->capacity = cap;
    stack->count = 0;
    return stack;
}

void destroy(Stack *stack){
    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
    stack->count = 0;
}
bool is_empty(Stack *stack){
    return (stack->count == 0);
}
bool is_full(Stack *stack){
    return (stack->count >= stack->capacity);
}
Stack *push(Stack *stack, char data){
    if (is_full(stack)){
        size_t new_capacity = stack->capacity == 0 ? 1: stack->capacity * 2; 
        char *temp = realloc(stack->data, new_capacity);
        if (!temp){
            return NULL;
        }
        stack->data = temp;
        stack->capacity = new_capacity;
    }
    stack->data[stack->count++] = data;
    return stack;
}
char pop(Stack *stack){
    if (!(is_empty(stack))) {
        return stack->data[--stack->count]; 
    }
    return '0';
}
char top(Stack *stack){
    if (!(is_empty(stack))) {
        return stack->data[stack->count - 1]; 
    }
    return '0';
}