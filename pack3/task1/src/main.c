#include "../include/header.h"

void test(int n, int r) {
    char result[BUFSIZ];
    status status = convert(n, r, result);

    switch (status)
    {
    case VALID:
        printf("%d = %s в 2^%d\n", n, result, r);
        break;
    
    case INVALID_INPUT:
        printf("Некорректные аргументы\n");
        break;
    
    default:
        printf("Неизвестная ошибка\n");
        break;
    }
}


int to_int(const char* str, int* res) {
    if (!str || !res) {
        return INVALID_INPUT;
    }

    int number = 0;
    const short base = 10;
    short sign = 1;

    const char* elem = str;

    while (*elem == ' ' || *elem == '\t') {
        elem++;
    }

    if (*elem == '-') {
        sign = -1;
        elem++;
    } else if (*elem == '+') {
        elem++;
    }

    if (!isdigit(*elem)) {
        return INVALID_INPUT; 
    }

    while (*elem) {
        if (!isdigit(*elem)) {       
            return INVALID_INPUT;
        }

        int digit = *elem - '0';

        if (number > (INT_MAX - digit) / 10) {
            return OVERFLOW_ERROR; 
        }

        number = number * base + digit;
        elem++;
    }

    number *= sign;
    *res = number;

    return VALID;
}

int main() {
    char input[BUFSIZ];
    int number;
    int r;

    while (1) {
        printf("Введите число (exit)\n");

        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "exit") == 0) break;

        int status = to_int(input, &number);

        if (status == INVALID_INPUT) {
            printf("Некорректный ввод. Введите целое число.\n\n");
            return INVALID_INPUT;
        } else if (status == OVERFLOW_ERROR) {
            printf("Ошибка: переполнение типа int.\n\n");
            return OVERFLOW_ERROR;
        }

        printf("Введите r\n");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        status = to_int(input, &r);

        if (status != VALID || r < 1 || r > 5) {
            printf("Некорректная степень r.\n\n");
            return INVALID_INPUT;
        }

        char result[BUFSIZ];
        status = convert(number, r, result);

        if (status == VALID) {
            printf("%d = %s в 2^%d\n\n", number, result, r);
        } else {
            printf("Ошибка конвертации.\n\n");
        }
    }

    return 0;
}
