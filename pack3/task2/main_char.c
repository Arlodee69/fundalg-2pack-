#define VECTOR_TYPE char
#include "vector.h"

char copy_char(char value) {
    return value;
}

void delete_char(char value) {
    (void)value;
}

int main() {
    Vector v = create_vector(2, copy_char, delete_char);

    push_back_vector(&v, 'A');
    push_back_vector(&v, 'B');
    push_back_vector(&v, 'C');

    printf("Testing Vector for char:\n");
    printf("Size: %zu, Capacity: %zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("Element %zu: %c\n", i, get_at_vector(&v, i));
    }

    delete_at_vector(&v, 0);
    printf("After deleting index 0:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("Element %zu: %c\n", i, get_at_vector(&v, i));
    }

    erase_vector(&v);
    return 0;
}