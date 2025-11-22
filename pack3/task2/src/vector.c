#include "../include/vector.h"


Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void(*DeleteFunc)(VECTOR_TYPE)){
    Vector v = {0};
    if (initial_capacity == 0) initial_capacity = 1;
    v.data = malloc(initial_capacity * sizeof(VECTOR_TYPE));
    if (!v.data) {
        v.size = 0;
        v.capacity = 0;
        v.CopyVoidPtr = CopyFunc;
        v.DeleteVoidPtr = DeleteFunc;
        return v;
    }
    v.capacity = initial_capacity;
    v.size = 0;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;
    return v;
}

void erase_vector(Vector *v){
    if (!v) return;
    if (v->DeleteVoidPtr){
        for (size_t i = 0; i < v->size; i++){
            v->DeleteVoidPtr(v->data[i]);
        }
    }
    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2, int (*comp)(VECTOR_TYPE, VECTOR_TYPE)){
    if (!v1 || !v2) return 0;
    if (v1->size != v2->size) return 0;

    for (size_t i = 0; i < v1->size; i++) {
        if (!comp(v1->data[i], v2->data[i])) return 0;
    }

    return 1;
}

void copy_vector(Vector *dest, const Vector *src){
    if (!dest || !src) return;
    if (!dest->CopyVoidPtr || !dest->DeleteVoidPtr) return;

    if (dest == src) return;
    erase_vector(dest);

    dest->data = malloc(src->capacity * sizeof(VECTOR_TYPE));
    if (!dest->data) {
        dest->size = 0;
        dest->capacity = 0;
        return;
    }

    dest->capacity = src->capacity;
    dest->size = src->size;

    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;

    for (size_t i = 0; i < src->size; i++) {
        dest->data[i] = dest->CopyVoidPtr(src->data[i]);
    }
}


Vector *copy_vector_new(const Vector *src){
    if (!src || !src->CopyVoidPtr || !src->DeleteVoidPtr)
        return NULL;

    Vector *new_v = malloc(sizeof(Vector));
    if (!new_v) return NULL;
    new_v->data = malloc(src->capacity * sizeof(VECTOR_TYPE));
    if (!new_v->data) {
        free(new_v);
        return NULL;
    }

    new_v->capacity = src->capacity;
    new_v->size = src->size;

    new_v->CopyVoidPtr = src->CopyVoidPtr;
    new_v->DeleteVoidPtr = src->DeleteVoidPtr;

    for (size_t i = 0; i < src->size; i++) {
        new_v->data[i] = src->CopyVoidPtr(src->data[i]);
    }

    return new_v;
}


void push_back_vector(Vector *v, VECTOR_TYPE value){
    if (!v || !v->CopyVoidPtr || !v->DeleteVoidPtr) return;
    if (v->size >= v->capacity) {
        size_t new_cap = v->capacity * 2;
        VECTOR_TYPE *new_data = realloc(v->data, new_cap * sizeof(VECTOR_TYPE));
        if (!new_data) return;
        v->data = new_data;
        v->capacity = new_cap;
    }
    v->data[v->size++] = v->CopyVoidPtr(value);
}

void delete_at_vector(Vector *v, size_t index){
    if (!v || !v->CopyVoidPtr || !v->DeleteVoidPtr) return;
    if (index >= v->size) return;
    v->DeleteVoidPtr(v->data[index]);
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;

    if (v->size * 2 <= v->capacity){
        v->capacity = v->capacity / 2;
        VECTOR_TYPE *newdata = realloc(v, v->capacity * sizeof(VECTOR_TYPE));
        if (!newdata) return;
        v->data = newdata;
    }
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index){
    if (!v || index >= v->size) {
        return (VECTOR_TYPE){0};
    }
    return v->data[index];
}

void delete_vector(Vector *v){
    if (!v) return;
    erase_vector(v);
    free(v);
}