#include "header.h"

int main(int argc, char* argv[]){
    char file_in[MAX_SIZE];
    if (scanf("%255s", file_in) == -1) return ARG_ERROR;
    char file_out[MAX_SIZE];
    if (scanf("%255s", file_out) == -1) return ARG_ERROR;

    char *real_in = realpath(file_in, NULL);
    char *real_out = realpath(file_out, NULL);

    if (!real_in || !real_out) {
        printf("Ошибка получения абсолютного пути\n");
        free(real_in);
        free(real_out);
        return FILE_ERROR;
    }

    if (strcmp(real_in, real_out) == 0) {
        printf("Введены одинаковые файлы на чтение и запись\n");
        free(real_in);
        free(real_out);
        return ARG_ERROR;
    }

    free(real_in);
    free(real_out);

    status_code some_code = parse_file(file_in, file_out);

    switch (some_code){
    case ALLOCATION_ERROR:
        printf("Allocation_Error\n");
    case FILE_ERROR:
        printf("File_Error\n");
        break;
    case ARG_ERROR:
        printf("Arg_error\n");
        break;
    case VALID:
        printf("Success\n");
        break;
    default:
        printf("Undefine_error\n");
        break;
    }
}