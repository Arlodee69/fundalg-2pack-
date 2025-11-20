#include "header.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Использование: %s <входной_файл> [трассировочный_файл]\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *trace_filename = (argc > 2) ? argv[2] : NULL;

    FILE *input = fopen(input_filename, "r");
    if (!input) {
        printf("Ошибка открытия входного файла\n");
        return FILE_ERROR;
    }

    if (trace_filename) {
        char *real_in = realpath(input_filename, NULL);
        char *real_trace = realpath(trace_filename, NULL);

        if (real_in && real_trace && strcmp(real_in, real_trace) == 0) {
            printf("Ошибка: Входной и трассировочный файлы совпадают.\n");
            free(real_in);
            free(real_trace);
            fclose(input);
            return FILE_ERROR;
        }
        free(real_in);
        free(real_trace);
    }

    Student *students = NULL;
    size_t student_count = 0;

    status_code result = reading(input, &students, &student_count);

    if (result != SUCCESS) {
        if (result == ALLOCATION_ERROR) {
            printf("Ошибка выделения памяти при загрузке данных\n");
        } else if (result == FILE_ERROR) {
            printf("Ошибка файла при загрузке данных\n");
        }
        return (result == ALLOCATION_ERROR) ? 2 : 1;
    }

    if (student_count == 0) {
        printf("Файл пуст или не содержит корректных данных\n");
        free_students(students, student_count);
        return 0;
    }

    printf("Данные о %zu студентах успешно обработаны\n", student_count);
    int choice;
    char input_str[MAX_STR_LEN];
    unsigned int input_id;
    bool running = true;

    while (running) {
        interaction();
        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод. Введите число\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                printf("Введите ID: ");
                if (scanf("%u", &input_id) == 1) {
                    int index = find_index_by_id(students, student_count, input_id);
                    if (index != -1) {
                        printf("Найден студент по ID %u:\n", input_id);
                        print_student_grades(&students[index]);
                    } else {
                        printf("Студент с ID %u не найден\n", input_id);
                    }
                } else {
                    printf("Некорректный ID\n");
                }
                break;
            }
            case 2: {
                printf("Введите фамилию: ");
                if (scanf("%99s", input_str) == 1) {
                    Student *results = NULL;
                    size_t results_count = 0;
                    result = find_students_by_lastname(students, student_count, input_str, &results, &results_count);
                    if (result == SUCCESS) {
                        if (results_count > 0) {
                            for (size_t i = 0; i < results_count; i++) {
                                print_student(&results[i]);
                            }
                        } else {
                            printf("Студенты с фамилией '%s' не найдены\n", input_str);
                        }
                    } else {
                        printf("Ошибка при поиске по фамилии\n");
                    }
                    free(results);
                } else {
                    printf("Некорректный ввод\n");
                }
                break;
            }
            case 3: {
                printf("Введите имя: ");
                if (scanf("%99s", input_str) == 1) {
                    Student *results = NULL;
                    size_t results_count = 0;
                    result = find_students_by_name(students, student_count, input_str, &results, &results_count);
                    if (result == SUCCESS) {
                        if (results_count > 0) {
                            for (size_t i = 0; i < results_count; i++) {
                                print_student(&results[i]);
                            }
                        } else {
                            printf("Студенты с именем '%s' не найдены\n", input_str);
                        }
                    } else {
                        printf("Ошибка при поиске по имени\n");
                    }
                    free(results);
                } else {
                    printf("Некорректный ввод\n");
                }
                break;
            }
            case 4: {
                printf("Введите группу: ");
                if (scanf("%99s", input_str) == 1) {
                    Student *results = NULL;
                    size_t results_count = 0;
                    result = find_students_by_group(students, student_count, input_str, &results, &results_count);
                    if (result == SUCCESS) {
                        if (results_count > 0) {
                            for (size_t i = 0; i < results_count; i++) {
                                print_student(&results[i]);
                            }
                        } else {
                            printf("Студенты из группы '%s' не найдены\n", input_str);
                        }
                    } else {
                        printf("Ошибка при поиске по группе\n");
                    }
                    free(results);
                } else {
                    printf("Некорректный ввод\n");
                }
                break;
            }
            case 5:
                qsort(students, student_count, sizeof(Student), compare_by_id);
                printf("Отсортировано по ID\n");
                break;
            case 6:
                qsort(students, student_count, sizeof(Student), compare_by_lastname);
                printf("Отсортировано по фамилии\n");
                print_students_list(students, student_count);
                break;
            case 7:
                qsort(students, student_count, sizeof(Student), compare_by_name);
                printf("Отсортировано по имени\n");
                print_students_list(students, student_count);
                break;
            case 8:
                qsort(students, student_count, sizeof(Student), compare_by_group);
                printf("Отсортировано по группе\n");
                print_students_list(students, student_count);
                break;
            case 9: {
                if (trace_filename) {
                    printf("Введите ID студента для вывода в трассировочный файл (%s): ", trace_filename);
                    if (scanf("%u", &input_id) == 1) {
                        FILE *trace = fopen(trace_filename, "w");
                        if (!trace) {
                            printf("Ошибка открытия трассировочного файла для записи");
                        } else {
                            result = write_student_to_trace_file(trace, students, student_count, input_id);
                            fclose(trace);
                            if (result == SUCCESS) {
                                printf("Данные студента с ID %u записаны в %s\n", input_id, trace_filename);
                            } else {
                                printf("Ошибка записи в трассировочный файл\n");
                            }
                        }
                    } else {
                        printf("Некорректный ID\n");
                    }
                } else {
                    printf("Трассировочный файл не указан при запуске программы\n");
                }
                break;
            }
            case 10: {
                if (trace_filename) {
                    FILE *trace = fopen(trace_filename, "w");
                    if (!trace) {
                        perror("Ошибка открытия трассировочного файла для записи");
                    } else {
                        result = write_above_average_to_trace_file(trace, students, student_count);
                        fclose(trace);
                        if (result == SUCCESS) {
                            printf("Список студентов с баллом выше среднего записан в %s\n", trace_filename);
                        } else {
                            printf("Ошибка записи в трассировочный файл\n");
                        }
                    }
                } else {
                    printf("Трассировочный файл не указан при запуске программы\n");
                }
                break;
            }
            case 11:
                print_students_list(students, student_count);
                break;
            case 0:
                running = false;
                break;
            default:
                printf("Некорректная опция\n");
                break;
        }
    }

    free_students(students, student_count);
    printf("Выход\n");
    return 0;
}