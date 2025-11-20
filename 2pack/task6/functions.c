#include "header.h"

status_code reading(FILE *input, Student **students, size_t *count){
    size_t temp_count = 0;
    char line[1024];
    while (fgets(line, sizeof(line), input) != NULL) {
        temp_count++;
    }
    rewind(input);

    if (temp_count == 0) {
        *students = NULL;
        *count = 0;
        fclose(input);
        return SUCCESS;
    }

    Student *temp_students = malloc(temp_count * sizeof(Student));
    if (!temp_students) {
        fclose(input);
        return ALLOCATION_ERROR;
    }

    size_t num_loaded = 0;
    unsigned int id;
    char name[MAX_STR_LEN], lastname[MAX_STR_LEN], group[MAX_STR_LEN];
    unsigned char grades[NUM_EXAMS];
    while (fgets(line, sizeof(line), input) != NULL) {

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        int ret = sscanf(line, "%u %99s %99s %99s %hhu %hhu %hhu %hhu %hhu", &id, name, lastname, group, &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]);
        if (ret != 9) {
            //fprintf(stderr, "Неверный формат строки '%s', пропущена.\n", line);
            continue;
        }
        bool name_ok = true, lastname_ok = true;
        for (int j = 0; name[j] != '\0'; j++) {
            if (!isalpha(name[j])) { 
                name_ok = false; 
                break; 
            }
        }
        for (int j = 0; lastname[j] != '\0'; j++) {
            if (!isalpha(lastname[j])) { 
                lastname_ok = false; 
                break; 
            }
        }

        if (!name_ok || !lastname_ok) {
            //fprintf(stderr, "Имя или фамилия содержат недопустимые символы, пропущена.\n");
            continue;
        }

        bool grades_valid = true;
        for (int j = 0; j < NUM_EXAMS; j++) {
            if (grades[j] > 5) {
                grades_valid = false;
                break;
            }
        }
        if (!grades_valid) {
            //fprintf(stderr, "Некорректная оценка, пропущена.\n");
            continue;
        }

        temp_students[num_loaded].id = id;
        strncpy(temp_students[num_loaded].name, name, MAX_STR_LEN - 1);
        temp_students[num_loaded].name[MAX_STR_LEN - 1] = '\0';
        strncpy(temp_students[num_loaded].lastname, lastname, MAX_STR_LEN - 1);
        temp_students[num_loaded].lastname[MAX_STR_LEN - 1] = '\0';
        strncpy(temp_students[num_loaded].group, group, MAX_STR_LEN - 1);
        temp_students[num_loaded].group[MAX_STR_LEN - 1] = '\0';

        temp_students[num_loaded].marks = malloc(NUM_EXAMS * sizeof(unsigned char));
        if (!temp_students[num_loaded].marks) {
            for (size_t k = 0; k < num_loaded; k++) {
                free(temp_students[k].marks);
            }
            free(temp_students);
            fclose(input);
            return ALLOCATION_ERROR;
        }
        memcpy(temp_students[num_loaded].marks, grades, NUM_EXAMS * sizeof(unsigned char));

        num_loaded++;
    }

    *students = realloc(temp_students, num_loaded * sizeof(Student));
    if (!(*students) && num_loaded > 0) {
        *students = temp_students;
    }
    *count = num_loaded;

    fclose(input);
    return SUCCESS;
}


void free_students(Student *students, size_t count) {
    if (students) {
        for (size_t i = 0; i < count; i++) {
            free(students[i].marks);
        }
        free(students);
    }
}


int find_index_by_id(Student *students, size_t count, unsigned int id) {
    for (size_t i = 0; i < count; i++) {
        if (students[i].id == id) {
            return (int)i;
        }
    }
    return -1;
}

status_code find_students_by_lastname(Student *students, size_t count, const char *lastname, Student **results, size_t *results_count) {

    if (!students || !lastname || !results || !results_count) return VALIDATION_ERROR;
    *results = malloc(count * sizeof(Student));
    if (!(*results)) return ALLOCATION_ERROR;

    size_t found_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].lastname, lastname) == 0) {
            if (found_count >= count) {
                free(*results);
                *results = NULL;
                return ALLOCATION_ERROR;
            }
            (*results)[found_count] = students[i];
            found_count++;
        }
    }
    *results_count = found_count;
    return SUCCESS;
}

status_code find_students_by_name(Student *students, size_t count, const char *name, Student **results, size_t *results_count) {
    if (!students || !name || !results || !results_count) return VALIDATION_ERROR;

    *results = malloc(count * sizeof(Student));
    if (!(*results)) return ALLOCATION_ERROR;

    size_t found_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            if (found_count >= count) {
                free(*results);
                *results = NULL;
                return ALLOCATION_ERROR;
            }
            (*results)[found_count] = students[i];
            found_count++;
        }
    }
    *results_count = found_count;
    return SUCCESS;
}

status_code find_students_by_group(Student *students, size_t count, const char *group, Student **results, size_t *results_count) {
    if (!students || !group || !results || !results_count) return VALIDATION_ERROR;

    *results = malloc(count * sizeof(Student));
    if (!(*results)) return ALLOCATION_ERROR;

    size_t found_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0){
            if (found_count >= count) {
                free(*results);
                *results = NULL;
                return ALLOCATION_ERROR;
            }
            (*results)[found_count] = students[i];
            found_count++;
        }
    }
    *results_count = found_count;
    return SUCCESS;
}


int compare_by_id(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    if (sa->id < sb->id) return -1;
    if (sa->id > sb->id) return 1;
    return 0;
}

int compare_by_lastname(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    return strcmp(sa->lastname, sb->lastname);
}

int compare_by_name(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    return strcmp(sa->name, sb->name);
}

int compare_by_group(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    return strcmp(sa->group, sb->group);
}

double get_average_grade(const Student *s) {
    unsigned long long sum = 0;
    for (int i = 0; i < NUM_EXAMS; i++){
        sum += s->marks[i];
    }
    return (double)sum / NUM_EXAMS;
}

status_code write_student_to_trace_file(FILE *tf, Student *students, size_t count, unsigned int id) {
    if (!tf || !students) return FILE_ERROR;

    int index = find_index_by_id(students, count, id);
    if (index == -1) {
        fprintf(tf, "Студент с ID %u не найден.\n", id);
        return SUCCESS;
    }

    double avg = get_average_grade(&students[index]);
    fprintf(tf, "ФИО: %s %s, Группа: %s, Средняя оценка: %.2f\n", students[index].name, students[index].lastname, students[index].group, avg);
    return SUCCESS;
}

status_code write_above_average_to_trace_file(FILE *tf, Student *students, size_t count){
    if (!tf || !students || count == 0) return FILE_ERROR;

    double total_avg = 0.0;
    for (size_t i = 0; i < count; i++) {
        total_avg += get_average_grade(&students[i]);
    }
    total_avg /= count;

    bool found_any = false;
    for (size_t i = 0; i < count; i++) {
        double avg = get_average_grade(&students[i]);
        if (avg > total_avg) {
            fprintf(tf, "%s %s\n", students[i].name, students[i].lastname);
            found_any = true;
        }
    }
    if (!found_any) {
        fprintf(tf, "Нет студентов с баллом выше среднего (%.2f)\n", total_avg);
    }
    return SUCCESS;
}

void interaction(){
    printf("\n--- Меню ---\n");
    printf("1. Найти по ID\n");
    printf("2. Найти по фамилии\n");
    printf("3. Найти по имени\n");
    printf("4. Найти по группе\n");
    printf("5. Сортировать по ID\n");
    printf("6. Сортировать по фамилии\n");
    printf("7. Сортировать по имени\n");
    printf("8. Сортировать по группе\n");
    printf("9. Вывести данные студента по ID в трассировочный файл\n");
    printf("10. Вывести студентов с баллом выше среднего в трассировочный файл\n");
    printf("11. Вывести всех студентов\n");
    printf("0. Выйти\n");
    printf("Выберите опцию: ");
}

void print_student(const Student *s) {
    if (s) {
        printf("ID: %u, Имя: %s, Фамилия: %s, Группа: %s\n", s->id, s->name, s->lastname, s->group);
    }
}

void print_student_grades(const Student *s) {
    if (s && s->marks) {
        printf("  Имя: %s\n", s->name);
        printf("  Фамилия: %s\n", s->lastname);
        printf("  Группа: %s\n", s->group);
        printf("  Оценки: ");
        for (int j = 0; j < NUM_EXAMS; j++) {
            printf("%hhu ", s->marks[j]);
        }
        printf("\n");
    }
}

void print_students_list(Student *students, size_t count) {
    printf("\nСписок всех студентов\n");
    for (size_t i = 0; i < count; i++) {
        print_student(&students[i]);
    }
    printf("Конец списка\n");
}