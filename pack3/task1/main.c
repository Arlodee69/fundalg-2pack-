#include "header.h"

int main() {
    unsigned int num;
    if (scanf("%d", &num) != 1) return INVALID_INPUT;

    char result[33];

    printf("1\n");
    switch (convert(num, 1, result))
    {
    case VALID:
        printf("%s\n", result);
        break;
    case INVALID_INPUT:
        printf("Неправильный ввод\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }

    printf("2\n");
    switch (convert(num, 2, result))
    {
    case VALID:
        printf("%s\n", result);
        break;
    case INVALID_INPUT:
        printf("Неправильный ввод\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }

    printf("3\n");
    switch (convert(num, 3, result))
    {
    case VALID:
        printf("%s\n", result);
        break;
    case INVALID_INPUT:
        printf("Неправильный ввод\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }

    printf("4\n");
    switch (convert(num, 4, result))
    {
    case VALID:
        printf("%s\n", result);
        break;
    case INVALID_INPUT:
        printf("Неправильный ввод\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }

    printf("5\n");
    switch (convert(num, 5, result))
    {
    case VALID:
        printf("%s\n", result);
        break;
    case INVALID_INPUT:
        printf("Неправильный ввод\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }
    return 0;
}