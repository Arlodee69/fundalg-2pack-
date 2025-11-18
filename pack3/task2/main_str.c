#define VECTOR_TYPE char*
#include "vector.h"

char* copy_char_ptr(char* value) {
    if (value == NULL) return NULL;
    size_t len = strlen(value) + 1;
    char* new_str = malloc(len);
    if (new_str) {
        strcpy(new_str, value);
    }
    return new_str;
}

void delete_char_ptr(char* value) {
    free(value);
}

int main() {
    Vector v = create_vector(2, copy_char_ptr, delete_char_ptr);

    char* s1 = "Hello";
    char* s2 = "World";
    char* s3 = "C Language";

    push_back_vector(&v, s1);
    push_back_vector(&v, s2);
    push_back_vector(&v, s3);

    printf("Testing Vector for char*:\n");
    printf("Size: %zu, Capacity: %zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        char* s = get_at_vector(&v, i);
        printf("Element %zu: %s\n", i, s);
    }

    delete_at_vector(&v, 1);
    printf("After deleting index 1:\n");
    for (size_t i = 0; i < v.size; i++) {
        char* s = get_at_vector(&v, i);
        printf("Element %zu: %s\n", i, s);
    }

    erase_vector(&v);
    return 0;
}