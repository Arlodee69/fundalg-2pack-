#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    VECTOR_TYPE *data;                  
    size_t size;                        
    size_t capacity;                    

    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);  
    void (*DeleteVoidPtr)(VECTOR_TYPE);
} Vector;

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
    if (v->DeleteVoidPtr){
        for (size_t i = 0; i < v->size; i++){
            v->DeleteVoidPtr(v->data[i]);
        }
    }
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2){
    if (v1->size != v2->size) return 0;
    for (size_t i = 0; i < v1->size; i++){
        if (memcmp(&v1->data[i], &v2->data[i], sizeof(VECTOR_TYPE)) != 0){
            return 0;
        }
    }
    return 1;
}

void copy_vector(Vector *dest, const Vector *src){
    if (dest->DeleteVoidPtr) {
        for (size_t i = 0; i < dest->size; i++) {
            dest->DeleteVoidPtr(dest->data[i]);
        }
    }
    if (dest->capacity < src->size) {
        VECTOR_TYPE *new_data = realloc(dest->data, src->size * sizeof(VECTOR_TYPE));
        if (!new_data) return;
        dest->data = new_data;
        dest->capacity = src->size;
    }
    dest->size = 0;
    for (size_t i = 0; i < src->size; i++) {
        dest->data[dest->size++] = src->CopyVoidPtr(src->data[i]);
    }
}

Vector *copy_vector_new(const Vector *src){
    Vector *new_v = malloc(sizeof(Vector));
    if (!new_v->data) {
        free(new_v);
        return NULL;
    }
    *new_v = create_vector(src->size, src->CopyVoidPtr, src->DeleteVoidPtr);
    copy_vector(new_v, src);
    return new_v;
}

void push_back_vector(Vector *v, VECTOR_TYPE value){
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
    if (index >= v->size) return;
    v->DeleteVoidPtr(v->data[index]);
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index){
    if (index >= v->size) {
        return (VECTOR_TYPE){0};
    }
    return v->data[index];
}

void delete_vector(Vector *v){
    free(v->data);
    free(v);
}
#endif
