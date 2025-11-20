#include "../include/person.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Person *create_person(const char *name, int age) {
    Person *p = malloc(sizeof(Person));
    if (!p) return NULL;

    p->name = malloc(strlen(name) + 1);
    if (!p->name) {
        free(p);
        return NULL;
    }
    strcpy(p->name, name);
    p->age = age;

    return p;
}

Person *copy_person(Person *src) {
    if (!src) return NULL;

    Person *p = malloc(sizeof(Person));
    if (!p) return NULL;

    p->name = malloc(strlen(src->name) + 1);
    if (!p->name) {
        free(p);
        return NULL;
    }

    strcpy(p->name, src->name);
    p->age = src->age;

    return p;
}

void delete_person(Person *p) {
    if (!p) return;
    free(p->name);
    free(p);
}

int compare_person(Person *a, Person *b) {
    int cmp = strcmp(a->name, b->name);
    if (cmp != 0) return cmp;
    return a->age - b->age;
}

void print_person(const Person *p) {
    printf("(%s, %d)", p->name, p->age);
}
