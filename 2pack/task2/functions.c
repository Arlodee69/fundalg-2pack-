#include "header.h"

void *memchr(const void *str, int c, size_t n){
    const unsigned char* ptr = (const unsigned char*)str;
    unsigned char find = (unsigned char) c;

    for (size_t i = 0; i < n; ++i){
        if (ptr[i] == find){
            return (void *)(ptr + i);
        }
    }
    
    return NULL;
}
int memcmp(const void *str1, const void *str2, size_t n){
    const unsigned char* ptr1 = (const unsigned char*)str1;
    const unsigned char* ptr2 = (const unsigned char*)str2;

    for (size_t i = 0; i < n; ++i){
        if (ptr1[i] != ptr2[i]) {
            return ptr1[i] - ptr2[i];
        }
    }
    return 0;
}
void *memcpy(void *dest, const void *src, size_t n){
    unsigned char *ptr1 = (unsigned char *)dest;
    const unsigned char *ptr2 = (const unsigned char *)src;

    for (size_t i = 0; i < n; ++i){
        ptr1[i] = ptr2[i];
    }
    return (void *)ptr1;
}
void *memset(void *str, int c, size_t n){
    unsigned char find = (unsigned char) c;
    unsigned char* ptr = (unsigned char *)str;
    
    for (size_t i = 0; i < n; ++i){
        ptr[i] = find;
    }

    return (void *)ptr;
}
char *strncat(char *dest, const char *src, size_t n){
    char *ret = dest;
    while(*dest != '\0'){
        dest++;
    }
    for(size_t i = 0; i < n && *src != '\0'; ++i){
        *dest = *src;
        src++;
        dest++;
    }
    *dest = '\0';
    return ret;
}
char *strchr(const char *str, int c){
    unsigned char find = (unsigned char) c;

    while(*str != '\0'){
        if (*str == find){
            return (char *)str;
        }
        str++;
    }

    if (*str == find){
        return (char *)str;
    }
    return NULL;
}
int strncmp(const char *str1, const char *str2, size_t n){
    const unsigned char *ptr1 = (const unsigned char *)str1;
    const unsigned char *ptr2 = (const unsigned char *)str2;

    for (size_t i = 0; i < n; i++) {
        if (ptr1[i] != ptr2[i]) {
            return ptr1[i] - ptr2[i];
        }
        if (ptr1[i] == '\0') { 
            break;
        }
    }
    return 0;
}
char *strncpy(char *dest, const char *src, size_t n){
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    for (i; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}
size_t strcspn(const char *str1, const char *str2){
    size_t count = 0;
    unsigned char set[256] = {0};

    const char *ptr = str2;
    while(*ptr != '\0'){
        set[(unsigned char)*ptr] = 1;
        ptr++;
    }

    while (str1[count] != '\0'){
        if (set[(unsigned char)str1[count]] == 1){
            return count;
        }
        count++;
    }
    return count;
}
/*char *strerror(int errnum);*/
size_t strlen(const char *str){
    size_t count = 0;
    while (*str != '\0'){
        count++;
        str++;
    }
    return count;
}
char *strpbrk(const char *str1, const char *str2){
    unsigned char set[256] = {0};
    const char *ptr = str2;
    while(*ptr != '\0'){
        set[(unsigned char)*ptr] = 1;
        ptr++;
    }
    size_t count = 0;
    while (str1[count] != '\0'){
        if (set[(unsigned char)str1[count]] == 1){
            return (char *)(str1 + count);
        }
        count++;
    }
    return NULL;
}
char *strrchr(const char *str, int c){
    char *last = NULL;
    while(*str != '\0'){
        if (*str == c){
            last = (char *)str;
        }
        str++;
    }

    if (*str == c){    // '\0'
       return (char *)str;
    }

    return last;
}
char *strstr(const char *haystack, const char *needle){
    if (*needle == '\0'){
        return(char *)haystack;
    }
    const char *h = haystack;
    while (*h != '\0'){
        const char *h_it = h;
        const char *n_it = needle;
        while (*n_it != '\0' && *n_it == *h_it){
            n_it++;
            h_it++;
        }
        if(*n_it == '\0'){
            return (char *)h;
        }
        h++;
    }

    return NULL;
}
char *strtok(char *str, const char *delim){
    static char *next_start = NULL;
    size_t i;

    if (str != NULL) {
        next_start = str;
    }

    if (next_start == NULL) {
        return NULL;
    }

    while (*next_start != '\0') {
        int found_delim = 0;
        for (i = 0; delim != NULL && delim[i] != '\0'; i++) {
            if (*next_start == delim[i]) {
                found_delim = 1;
                break;
            }
        }
        if (!found_delim) {
            break;
        }
        next_start++;
    }

    if (*next_start == '\0') {
        next_start = NULL;
        return NULL;
    }

    char *token_start = next_start;

    while (*next_start != '\0') {
        int found_delim = 0;
        for (i = 0; delim != NULL && delim[i] != '\0'; i++) {
            if (*next_start == delim[i]) {
                found_delim = 1;
                break;
            }
        }
        if (found_delim) {
            break;
        }
        next_start++;
    }

    if (*next_start != '\0') {
        *next_start = '\0';
        next_start++;
    } else {
        next_start = NULL;
    }

    return token_start;
}