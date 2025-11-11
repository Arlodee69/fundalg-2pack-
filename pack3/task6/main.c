#include "header.h"

int main(int argc, char *argv[]){
    if (argc != 1) return 1;
    char line[1024];

    printf("Введите строку (Введите STOP для выхода) \n");
    while (true) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "STOP") == 0) {
            break;
        }
        if (strlen(line) == 0) {
            printf("Пустая строка\n");
            continue;
        }

        int result = check_brackets(line);

        switch (result){
        case (1):
            printf("Строка корректно сбалансирована по скобкам\n");
            break;
        case (0):
            printf("Строка некорректно сбалансирована по скобкам\n");
            break;
        case (-1):
            printf("Некорректные входные данные\n");
            break;
        }
    }
    return 0;
}