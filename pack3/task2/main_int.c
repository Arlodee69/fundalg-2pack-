#define VECTOR_TYPE int
#include "vector.h"

int copy_int(int value) {
    return value;
}

void delete_int(int value) {
    (void)value;
}

int main() {
    Vector v = create_vector(2, copy_int, delete_int);

    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);

    printf("Testing Vector for int:\n");
    printf("Size: %zu, Capacity: %zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("Element %zu: %d\n", i, get_at_vector(&v, i));
    }

    delete_at_vector(&v, 1);
    printf("After deleting index 1:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("Element %zu: %d\n", i, get_at_vector(&v, i));
    }

    erase_vector(&v);
    return 0;
}