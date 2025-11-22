#include <stdio.h>
#include <stdlib.h>

#include "../include/vector.h"

int copy_int(int value) {
    return value;
}

void delete_int(int value) {
    (void)value;
}

int compare_int(int a, int b) {
    return a == b;
}

void print_vector_int(const char* name, const Vector* v) {
    printf("%s [size=%zu, cap=%zu]: ", name, v->size, v->capacity);
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", get_at_vector(v, i));
    }
    printf("\n");
}


int main() {
    printf("Создание вектора int\n");
    Vector v = create_vector(2, copy_int, delete_int);
    print_vector_int("v", &v);

    printf("\npush_back_vector\n");
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    print_vector_int("v", &v);

    printf("\nget_at_vector\n");
    printf("v[1] = %d\n", get_at_vector(&v, 1));

    printf("\ndelete_at_vector (элемент 1)\n");
    delete_at_vector(&v, 1);
    print_vector_int("v", &v);

    printf("\ncopy_vector_new\n");
    Vector* v2 = copy_vector_new(&v);
    print_vector_int("v2", v2);

    printf("\nis_equal_vector (v == v2?)\n");
    int eq = is_equal_vector(&v, v2, compare_int);
    printf("Результат сравнения: %s\n", eq ? "EQUAL" : "NOT EQUAL");

    printf("\npush_back_vector в v2\n");
    push_back_vector(v2, 999);
    print_vector_int("v2", v2);

    printf("\nis_equal_vector (v == v2?)\n");
    eq = is_equal_vector(&v, v2, compare_int);
    printf("Результат сравнения: %s\n", eq ? "EQUAL" : "NOT EQUAL");

    printf("\ncopy_vector (копируем v в v2)\n");
    copy_vector(v2, &v);
    print_vector_int("v2", v2);

    eq = is_equal_vector(&v, v2, compare_int);
    printf("Сравнение после copy_vector: %s\n", eq ? "EQUAL" : "NOT EQUAL");

    printf("\nerase_vector v\n");
    erase_vector(&v);
    print_vector_int("v", &v);

    printf("\ndelete_vector v2\n");
    delete_vector(v2);
    
    return 0;
}
