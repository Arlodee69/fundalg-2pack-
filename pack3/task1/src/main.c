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

int main() {
    test(5, 2);
    test(5, 1);
    test(5, 3);
    test(102, 6);     //INVALID_INPUT
    test(0, 1);
    test(15, 1);
    test(77, 3);
    test(-77, 3);
    test(123456, 5);
    test(4095, 4);
    test(4096, 4); 
    test(63, 5);
    test(64, 5);
}
