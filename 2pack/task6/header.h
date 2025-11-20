#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR_LEN 100
#define NUM_EXAMS 5

typedef enum{
    SUCCESS = 0,
    FILE_ERROR = 1,
    ALLOCATION_ERROR = 2,
    VALIDATION_ERROR = 3,
} status_code;

typedef struct {
    unsigned int id;
    char name[MAX_STR_LEN];
    char lastname[MAX_STR_LEN];
    char group[MAX_STR_LEN];
    unsigned char *marks;
} Student;

status_code reading(FILE *input, Student **students, size_t *count);
void free_students(Student *students, size_t count);

int find_index_by_id(Student *students, size_t count, unsigned int id);
status_code find_students_by_lastname(Student *students, size_t count, const char *lastname, Student **results, size_t *results_count);
status_code find_students_by_name(Student *students, size_t count, const char *name, Student **results, size_t *results_count);
status_code find_students_by_group(Student *students, size_t count, const char *group, Student **results, size_t *results_count);

int compare_by_id(const void *a, const void *b);
int compare_by_lastname(const void *a, const void *b);
int compare_by_name(const void *a, const void *b);
int compare_by_group(const void *a, const void *b);

double get_average_grade(const Student *s);

status_code write_student_to_trace_file(FILE *tf, Student *students, size_t count, unsigned int id);
status_code write_above_average_to_trace_file(FILE *tf, Student *students, size_t count);
void interaction();
void print_student(const Student *s);
void print_student_grades(const Student *s);
void print_students_list(Student *students, size_t count); 

#endif