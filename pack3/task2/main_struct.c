typedef struct {
    int id;
    char name[32];
} Person;

#define VECTOR_TYPE Person
#include "vector.h"

Person copy_person(Person value) {
    return value;
}

void delete_person(Person value) {
    (void)value;
}

int main() {
    Vector v = create_vector(2, copy_person, delete_person);

    Person p1 = { .id = 1, .name = "Alice" };
    Person p2 = { .id = 2, .name = "Bob" };
    Person p3 = { .id = 3, .name = "Charlie" };

    push_back_vector(&v, p1);
    push_back_vector(&v, p2);
    push_back_vector(&v, p3);

    printf("Testing Vector for Person:\n");
    printf("Size: %zu, Capacity: %zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        Person p = get_at_vector(&v, i);
        printf("Element %zu: id = %d, name = %s\n", i, p.id, p.name);
    }

    delete_at_vector(&v, 1);
    printf("After deleting index 1:\n");
    for (size_t i = 0; i < v.size; i++) {
        Person p = get_at_vector(&v, i);
        printf("Element %zu: id = %d, name = %s\n", i, p.id, p.name);
    }

    erase_vector(&v);
    return 0;
}