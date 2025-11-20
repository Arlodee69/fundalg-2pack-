#include "header.h"

int main() {
    const char a1[] = "algorithm";
    const char a2[] = "log";
    const char a3[] = "xyz";
    const char a4[] = "C\0language";
    const char a5[] = "test\0case";
    char b1[20] = "abcdefghij";
    char b2[20] = "##########";
    char b3[30] = "Prefix: ";
    char b4[15] = "overwrite me";
    char b5[20] = "  spaces  ";
    char b6[25] = "red,green,blue";
    char b7[20];
    char b8[50] = "The quick brown fox jumps";
    const char a6[] = "gfalgorithm";

    printf("--- Функция memchr ---\n");
    printf("%c\n", *(char *)memchr(a1, 'r', 8));
    printf("%p\n", memchr(a1, 'z', 10));

    printf("--- Функция memcmp ---\n");
    printf("%d\n", memcmp(a1, a2, 4));
    printf("%d\n", memcmp(a1, a2, 2));
    printf("%d\n", memcmp("alpha", "beta", 3));

    printf("--- Функция memcpy ---\n");
    memcpy(b2, a1, 6);
    printf("%s\n", b2);
    memcpy(b2 + 6, "123", 3);
    printf("%s\n", b2);

    printf("--- Функция memset ---\n");
    memset(b1, '-', 8);
    printf("%s\n", b1);

    printf("--- Функция strncat ---\n");
    strncat(b3, a1, 5);
    printf("%s\n", b3);

    printf("--- Функция strchr ---\n");
    printf("%p\n", strchr(a1, 'g'));
    printf("%p\n", strchr(a1, 'z'));

    printf("--- Функция strncmp ---\n");
    printf("%d\n", strncmp(a1, a2, 5));
    printf("%d\n", strncmp(a1, a2, 3));
    printf("%d\n", strncmp(a4, a5, 6));

    printf("--- Функция strncpy ---\n");
    strncpy(b4, a4, 10);
    printf("%s\n", b4);
    strncpy(b7, a3, 3);
    b7[3] = '\0';
    printf("%s\n", b7);

    printf("--- Функция strcspn ---\n");
    printf("%zu\n", strcspn(a1, a3));
    printf("%zu\n", strcspn(a6, "aeiou"));

    printf("--- Функция strlen ---\n");
    printf("%zu\n", strlen(a1));
    printf("%zu\n", strlen(b3));

    printf("--- Функция strpbrk ---\n");
    printf("%c\n", *strpbrk(a1, a2));
    printf("%p\n", strpbrk(a1, a3));

    printf("--- Функция strrchr ---\n");
    printf("%p\n", strrchr(a1, 'i'));
    printf("%p\n", strrchr(a1, 'z'));

    printf("--- Функция strstr ---\n");
    char *r1 = strstr(b8, "brown");
    if (r1) printf("%s\n", r1); else printf("Not found\n");
    char *r2 = strstr(b8, "lazy");
    if (r2) printf("%s\n", r2); else printf("Not found\n");
    char *r4 = strstr("Start here", "here");
    if (r4) printf("%c\n", *r4); else printf("Not found\n");

    printf("--- Функция strtok ---\n");
    char temp[] = "cat,dog;bird:fish";
    printf("%s\n", strtok(temp, ",;:"));
    printf("%s\n", strtok(NULL, ",;:"));
    printf("%s\n", strtok(NULL, ",;:"));
    printf("%s\n", strtok(NULL, ",;:"));

    return 0;
}