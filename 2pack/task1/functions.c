#include "header.h"


int gcd(int a, int b){
    while (b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

status_code hasFinish(double num, int base){
    char buff[128];
    snprintf(buff, sizeof(buff), "%.15f", num); 
    char *finddot = strchr(buff, '.');
    char *afterdot = finddot + 1;

    long long num_len = 0;
    while(isdigit(afterdot[num_len])) num_len++;

    if (num_len == 0) return INVALID;

    while (num_len > 0 && afterdot[num_len - 1] == '0') num_len--;

    if (num_len == 0) return INVALID;

    long long up = 0;
    for (long long i = 0; i < num_len; i++) {
        up = up * 10 + (afterdot[i] - '0');
    }
    long long down = 1;
    for (long long i = 0; i < num_len; i++) {
        down *= 10;
    }
    int nums_gcd = gcd(up, down);
    down /= nums_gcd;

    int b = base;
    for (int p = 2; p * p <= b; p++){
        if (b % p == 0){
            while (down % p == 0) {
                down /= p;
            }
            while (b % p == 0) {
                b /= p;
            }
        }
    }
    if (b > 1) {
        while (down % b == 0) {
            down /= b;
        }
    }
    if (down == 1) return YES;
    return NO;
}   

status_code to_int(const char* str, int* res) {
    if (!str || !res) {
        return INVALID;
    }

    int number = 0;
    const short base = 10;
    short sign = 1;

    const char* elem = str;

    while (*elem == ' ' || *elem == '\t') {
        elem++;
    }

    if (*elem == '-') {
        sign = -1;
        elem++;
    } else if (*elem == '+') {
        elem++;
    }

    if (!isdigit(*elem)) {
        return INVALID; 
    }

    while (*elem) {
        if (!isdigit(*elem)) {       
            return INVALID;
        }

        int digit = *elem - '0';

        if (number > (INT_MAX - digit) / 10) {
            return OVERFLOW_ERROR; 
        }

        number = number * base + digit;
        elem++;
    }

    number *= sign;
    *res = number;

    return VALID;
}

status_code check(int n, int base, ...){
    if (base < 2 || n <= 0) return INVALID;

    va_list args;
    va_start(args, base);

    printf("Проверка %d чисел в системе с основанием %d:\n", n, base);
    for (int i = 0; i < n; ++i) {
        double num = va_arg(args, double);
        if (num <= 0.0 || num >= 1.0){
            printf("Выход за допустимый диапазон\n"); 
            return INVALID;
        }
        status_code function = hasFinish(num, base);
        switch (function)
        {
        case YES:
            printf("Число %.17lf имеет конечное представление в СС %d\n", num, base);
            break;
        case NO:
            printf("Число %.17lf не имеет конечного представления в СС %d\n", num, base);
            break;
        default:
            printf("Unexpected error\n");
            break;
        }
    }

    va_end(args);
    return VALID;
}

int main(int argc, char* argv[]){
    if (argc != 2) return INVALID;

    int base;
    to_int(argv[1], &base);
    if (base < 2 || base > INT_MAX) return INVALID;
    
    double frac1 = 0.125;
    double frac2 = 0.1;
    double frac3 = 0.5;
    double frac4 = 0.320;
    double frac5 = 0.24354;

    check(5, base, frac1, frac2, frac3, frac4, frac5);

    return 0;
}  