#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/vector.h"


char* copy_char_ptr(char* value) {
    if (value == NULL) return NULL;
    size_t len = strlen(value) + 1;
    char* new_str = malloc(len);
    if (new_str) strcpy(new_str, value);
    return new_str;
}

void delete_char_ptr(char* value) {
    free(value);
}

int compare_char_ptr(char* a, char* b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    return strcmp(a, b) == 0;
}

void print_vector(const char* name, const Vector* v) {
    printf("%s [size=%zu, cap=%zu]: ", name, v->size, v->capacity);
    for (size_t i = 0; i < v->size; i++) {
        printf("\"%s\" ", get_at_vector(v, i));
    }
    printf("\n");
}

int main() {
    printf("Создание вектора \n");
    Vector v = create_vector(2, copy_char_ptr, delete_char_ptr);
    print_vector("v", &v);

    printf("\npush_back_vector\n");
    push_back_vector(&v, "Alpha");
    push_back_vector(&v, "Beta");
    push_back_vector(&v, "Gamma");
    print_vector("v", &v);

    printf("\nget_at_vector\n");
    printf("v[1] = %s\n", get_at_vector(&v, 1));

    printf("\ndelete_at_vector (элемент 1)\n");
    delete_at_vector(&v, 1);
    print_vector("v", &v);

    printf("\ncopy_vector_new\n");
    Vector* v2 = copy_vector_new(&v);
    print_vector("v2", v2);

    printf("\nis_equal_vector (v == v2?)\n");
    int eq = is_equal_vector(&v, v2, compare_char_ptr);
    printf("Результат сравнения: %s\n", eq ? "EQUAL" : "NOT EQUAL");

    printf("\npush_back_vector в v2\n");
    push_back_vector(v2, "Delta");
    print_vector("v2", v2);

    printf("\nis_equal_vector (v == v2?)\n");
    eq = is_equal_vector(&v, v2, compare_char_ptr);
    printf("Результат сравнения: %s\n", eq ? "EQUAL" : "NOT EQUAL");

    printf("\ncopy_vector (копируем v в v2)\n");
    copy_vector(v2, &v);
    print_vector("v2", v2);
    eq = is_equal_vector(&v, v2, compare_char_ptr);
    printf("Сравнение после copy_vector: %s\n", eq ? "EQUAL" : "NOT EQUAL");

    printf("\nerase_vector v\n");
    erase_vector(&v);
    print_vector("v", &v);

    printf("\ndelete_vector v2\n");
    delete_vector(v2);

    return 0;
}