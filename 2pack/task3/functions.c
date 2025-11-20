#include "header.h"

char digit_to_char(int digit) {
    if (digit < 10) return '0' + digit;
    return 'a' + digit - 10;
}

char digit_to_char_upper(int digit) {
    if (digit < 10) return '0' + digit;
    return 'A' + digit - 10;
}

int char_to_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

void convert_to_base(char *buffer, long long num, int base, int upper) {
    if (base < 2 || base > 36) base = 10;

    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int negative = 0;
    unsigned long long unum;
    if (num < 0) {
        negative = 1;
        unum = -num;
    } else {
        unum = num;
    }

    char temp[65];
    int len = 0;

    while (unum > 0) {
        int digit = unum % base;
        temp[len++] = upper ? digit_to_char_upper(digit) : digit_to_char(digit);
        unum /= base;
    }

    int idx = 0;
    if (negative) buffer[idx++] = '-';
    for (int i = len - 1; i >= 0; i--) {
        buffer[idx++] = temp[i];
    }
    buffer[idx] = '\0';
}

long long convert_from_base(const char *str, int base) {
    if (base < 2 || base > 36) base = 10;

    long long result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; str[i] != '\0'; i++) {
        int digit = char_to_digit(str[i]);
        if (digit == -1 || digit >= base) break;
        result = result * base + digit;
    }

    return sign * result;
}

void int_to_roman(char *buffer, int num) {
    if (num <= 0 || num > 3999) {
        strcpy(buffer, "OUT_OF_RANGE");
        return;
    }

    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    buffer[0] = '\0';
    int idx = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            const char* sym = symbols[i];
            while (*sym) {
                buffer[idx++] = *sym++;
            }
            num -= values[i];
        }
    }
    buffer[idx] = '\0';
}

unsigned int fib[MAX_FIB];

void generate_fib() {
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < MAX_FIB; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

void zeckendorf(unsigned int num, char *buffer) {
    if (num == 0) {
        strcpy(buffer, "01");
        return;
    }

    generate_fib();

    char temp[MAX_FIB + 2];
    int idx = 0;
    int started = 0;

    int start_idx = 0;
    for (int i = MAX_FIB - 1; i >= 0; i--) {
        if (fib[i] <= num) {
            start_idx = i;
            break;
        }
    }

    for (int i = start_idx; i >= 0; i--) {
        if (num >= fib[i]) {
            temp[idx++] = '1';
            num -= fib[i];
            started = 1;
        } else if (started) {
            temp[idx++] = '0';
        }
    }
    
    temp[idx++] = '1';
    temp[idx] = '\0';
    
    strcpy(buffer, temp);
}

void print_memory_dump(void *ptr, size_t size, char *buffer) {
    unsigned char *bytes = (unsigned char *)ptr;
    buffer[0] = '\0';
    int idx = 0;

    for (size_t i = 0; i < size; i++) {
        if (i > 0) {
            buffer[idx++] = ' ';
        }
        unsigned char b = bytes[i];
        for (int j = 7; j >= 0; j--) {
            buffer[idx++] = ((b >> j) & 1) ? '1' : '0';
        }
    }
    buffer[idx] = '\0';
}

int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int result = 0;
    const char *p = format;
    char buffer[4096];
    char *buf_ptr = buffer;
    
    while (*p) {
        if (*p != '%') {
            *buf_ptr++ = *p++;
            result++;
            continue;
        }
        
        p++;
        if (*p == '%') {
            *buf_ptr++ = '%';
            p++;
            result++;
            continue;
        }

        if (strncmp(p, "Ro", 2) == 0) {
            int num = va_arg(args, int);
            char roman[20];
            int_to_roman(roman, num);
            int len = strlen(roman);
            strcpy(buf_ptr, roman);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "Zr", 2) == 0) {
            unsigned int num = va_arg(args, unsigned int);
            char zstr[50];
            zeckendorf(num, zstr);
            int len = strlen(zstr);
            strcpy(buf_ptr, zstr);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "Cv", 2) == 0) {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char temp[65];
            convert_to_base(temp, num, base, 0);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "CV", 2) == 0) {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char temp[65];
            convert_to_base(temp, num, base, 1);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "to", 2) == 0) {
            char *str_arg = va_arg(args, char *);
            int base = va_arg(args, int);
            long long val = convert_from_base(str_arg, base);
            char temp[21];
            sprintf(temp, "%lld", val);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "TO", 2) == 0) {
            char *str_arg = va_arg(args, char *);
            int base = va_arg(args, int);
            long long val = convert_from_base(str_arg, base);
            char temp[21];
            sprintf(temp, "%lld", val);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "mi", 2) == 0) {
            int val = va_arg(args, int);
            char temp[100];
            print_memory_dump(&val, sizeof(int), temp);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "mu", 2) == 0) {
            unsigned int val = va_arg(args, unsigned int);
            char temp[100];
            print_memory_dump(&val, sizeof(unsigned int), temp);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "md", 2) == 0) {
            double val = va_arg(args, double);
            char temp[100];
            print_memory_dump(&val, sizeof(double), temp);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }
        else if (strncmp(p, "mf", 2) == 0) {
            float val = (float)va_arg(args, double);
            char temp[100];
            print_memory_dump(&val, sizeof(float), temp);
            int len = strlen(temp);
            strcpy(buf_ptr, temp);
            buf_ptr += len;
            result += len;
            p += 2;
            continue;
        }

        const char *spec_start = p - 1;

        while (*p && !strchr("diouxXeEfFgGaAcspn", *p)) {
            p++;
        }
        
        if (*p) {
            p++;
        }

        int spec_len = p - spec_start;
        char spec_buf[32];
        strncpy(spec_buf, spec_start, spec_len);
        spec_buf[spec_len] = '\0';

        char temp_buf[256];
        va_list args_copy;
        va_copy(args_copy, args);
        int printed = vsnprintf(temp_buf, sizeof(temp_buf), spec_buf, args_copy);
        va_end(args_copy);

        char spec_char = spec_buf[spec_len - 1];
        switch (spec_char) {
            case 'd': case 'i': case 'c':
                va_arg(args, int);
                break;
            case 'u': case 'o': case 'x': case 'X':
                va_arg(args, unsigned int);
                break;
            case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A':
                va_arg(args, double);
                break;
            case 's': case 'p':
                va_arg(args, void*);
                break;
            case 'n':
                va_arg(args, int*);
                break;
        }
        
        if (printed > 0) {
            strcpy(buf_ptr, temp_buf);
            buf_ptr += printed;
            result += printed;
        }
    }
    
    *buf_ptr = '\0';
    fputs(buffer, stream);
    
    va_end(args);
    return result;
}

int oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    FILE *stream = fopen("/dev/null", "w");
    if (!stream) {
        va_end(args);
        return -1;
    }

    int result = overfprintf(stream, format, args);

    va_end(args);
    va_start(args, format);
    vsprintf(str, format, args);
    va_end(args);
    
    fclose(stream);
    return result;
}