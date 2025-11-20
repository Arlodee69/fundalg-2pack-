#ifndef PERSON_H
#define PERSON_H

typedef struct {
    char *name;
    int age;
} Person;

Person *create_person(const char *name, int age);
Person *copy_person(Person *src);
void delete_person(Person *p);
int compare_person(Person *a, Person *b);
void print_person(const Person *p);

#endif
