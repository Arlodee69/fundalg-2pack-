#include "header.h"

int main(){
    char line[BUFSIZ];

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

        status result = check_brackets(line);

        switch (result){
        case (CORRECT):
            printf("Строка корректно сбалансирована по скобкам\n");
            break;
        case (INCORRECT):
            printf("Строка некорректно сбалансирована по скобкам\n");
            break;
        case (UNDEFINE):
            printf("Некорректные входные данные\n");
            break;
        }
    }
    return 0;
}