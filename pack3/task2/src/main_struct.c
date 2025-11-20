#include "../include/person.h"
#include "../include/vector.h"
#include <stdio.h>

void print_vector(const Vector *v, void (*print_elem)(const void *)) {
    printf("[size=%zu, cap=%zu]: ", v->size, v->capacity);
    for (size_t i = 0; i < v->size; i++) {
        print_elem(v->data[i]);
        printf(" ");
    }
    printf("\n");
}

int main() {
    printf("=== Создание вектора Person ===\n");
    Vector v = create_vector(2, copy_person, delete_person);
    print_vector(&v, (void (*)(const void *))print_person);

    printf("\n=== push_back_vector ===\n");
    push_back_vector(&v, create_person("Alice", 25));
    push_back_vector(&v, create_person("Bob", 30));
    push_back_vector(&v, create_person("Charlie", 20));
    print_vector(&v, (void (*)(const void *))print_person);

    printf("\n=== get_at_vector ===\n");
    Person *p = get_at_vector(&v, 1);
    print_person(p);
    printf("\n");

    printf("\n=== delete_at_vector (index=1) ===\n");
    delete_at_vector(&v, 1);
    print_vector(&v, (void (*)(const void *))print_person);

    printf("\n=== copy_vector_new ===\n");
    Vector *v2 = copy_vector_new(&v);
    print_vector(v2, (void (*)(const void *))print_person);

    printf("\n=== Проверка независимости копии ===\n");
    v2->data[0]->age = 99;
    strcpy(v2->data[0]->name, "ZZZZ");
    print_vector(&v, (void (*)(const void *))print_person);
    print_vector(v2, (void (*)(const void *))print_person);

    erase_vector(&v);

    erase_vector(v2);
    free(v2);

    return 0;
}
