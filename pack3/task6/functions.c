#include "header.h"

bool is_open_skobka(char c){
    return c == '{' || c == '(' || c == '[' || c == '<';
}

bool is_close_skobka(char c){
    return c == '}' || c == ')' || c == ']' || c == '>';
}

bool matches(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}') || (open == '<' && close == '>');
}

int check_brackets(const char *str){
    if (!str) return -1;

    Stack stack;
    create(&stack, 10);

    for (size_t i = 0; str[i] != '\0'; i++){

        if(is_open_skobka(str[i])){
            push(&stack, str[i]);
        }

        else if(is_close_skobka(str[i])){

            if(is_empty(&stack)){
                return 0;
            }

            char up = pop(&stack);
            if (!matches(up, str[i])){
                return 0;
            }
        }
    }

    int result = is_empty(&stack) ? 1 : 0;
    destroy(&stack);
    return result;
}