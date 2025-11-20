#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>

// Объявления функций
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

int main() {
    char buffer[10000];
    
    printf("=== ТЕСТ 1: СТАНДАРТНЫЕ СПЕЦИФИКАТОРЫ ===\n");
    
    printf("--- Целые числа ---\n");
    overfprintf(stdout, "%%d: %d\n", 42);
    overfprintf(stdout, "%%d отрицательное: %d\n", -123);
    overfprintf(stdout, "%%i: %i\n", 42);
    overfprintf(stdout, "%%x: %x\n", 255);
    overfprintf(stdout, "%%X: %X\n", 255);
    overfprintf(stdout, "%%o: %o\n", 64);
    overfprintf(stdout, "%%u: %u\n", 4294967295U);
    
    oversprintf(buffer, "Ширина 10: |%10d|", 42);
    printf("%s\n", buffer);
    oversprintf(buffer, "Ширина 10, нули: |%010d|", 42);
    printf("%s\n", buffer);
    oversprintf(buffer, "Флаг +: %+d %+d\n", 42, -42);
    printf("%s", buffer);
    oversprintf(buffer, "Флаг #: %#x %#o\n", 255, 64);
    printf("%s", buffer);
    oversprintf(buffer, "Флаг пробел: % d % d\n", 42, -42);
    printf("%s", buffer);
    
    printf("\n--- Вещественные числа ---\n");
    overfprintf(stdout, "%%f: %f\n", 3.1415926535);
    overfprintf(stdout, "%%f отрицательное: %f\n", -2.71828);
    overfprintf(stdout, "%%e: %e\n", 1234.5678);
    overfprintf(stdout, "%%E: %E\n", 1234.5678);
    overfprintf(stdout, "%%g: %g\n", 1234.5678);
    overfprintf(stdout, "%%G: %G\n", 12345678.0);
    
    oversprintf(buffer, "Точность 2: %.2f", 3.14159);
    printf("%s\n", buffer);
    oversprintf(buffer, "Ширина и точность: %10.3f", 3.14159);
    printf("%s\n", buffer);
    oversprintf(buffer, "Научная с точностью: %.2e", 1234.5678);
    printf("%s\n", buffer);
    
    printf("\n--- Строки и символы ---\n");
    overfprintf(stdout, "%%s: %s\n", "Hello, World!");
    overfprintf(stdout, "%%s пустая: %s\n", "");
    overfprintf(stdout, "%%c: %c\n", 'A');
    overfprintf(stdout, "%%c специальный: %c\n", '\n');
    
    oversprintf(buffer, "Ширина строки: |%10s|", "Hi");
    printf("%s\n", buffer);
    oversprintf(buffer, "Точность строки: |%.3s|", "Hello");
    printf("%s\n", buffer);
    oversprintf(buffer, "Символ как число: %c = %d\n", 'A', 'A');
    printf("%s", buffer);
    
    printf("\n--- Указатели и специальные ---\n");
    int test_var = 100;
    int n_val;
    overfprintf(stdout, "%%p: %p\n", (void*)&test_var);
    overfprintf(stdout, "%%p NULL: %p\n", NULL);
    
    oversprintf(buffer, "Тест %%n: %d%n переменная", 42, &n_val);
    printf("%s (n_val = %d)\n", buffer, n_val);
    
    printf("\n--- Модификаторы длины ---\n");
    long l_val = 1234567890L;
    long long ll_val = 123456789012345LL;
    unsigned long ul_val = 4294967295UL;
    short s_val = 12345;
    unsigned short us_val = 65535;
    
    overfprintf(stdout, "%%ld: %ld\n", l_val);
    overfprintf(stdout, "%%lld: %lld\n", ll_val);
    overfprintf(stdout, "%%lu: %lu\n", ul_val);
    overfprintf(stdout, "%%hd: %hd\n", s_val);
    overfprintf(stdout, "%%hu: %hu\n", us_val);
    
    printf("\n=== ТЕСТ 2: КАСТОМНЫЕ СПЕЦИФИКАТОРЫ ===\n");
    
    printf("--- %%Ro (римские цифры) ---\n");
    int roman_tests[] = {1, 4, 9, 42, 99, 444, 888, 1994, 1999, 2000, 3999, 0, -1, 4000, 10000};
    for (int i = 0; i < sizeof(roman_tests)/sizeof(roman_tests[0]); i++) {
        oversprintf(buffer, "%d -> %%Ro: %Ro", roman_tests[i], roman_tests[i]);
        printf("%s\n", buffer);
    }
    
    printf("\n--- %%Zr (цекендорфово представление) ---\n");
    unsigned int zeck_tests[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 50, 100, 1000};
    for (int i = 0; i < sizeof(zeck_tests)/sizeof(zeck_tests[0]); i++) {
        oversprintf(buffer, "%u -> %%Zr: %Zr", zeck_tests[i], zeck_tests[i]);
        printf("%s\n", buffer);
    }
    
    printf("\n--- %%Cv и %%CV (системы счисления) ---\n");
    struct base_test {
        int num;
        int base;
    } base_tests[] = {
        {255, 16}, {-255, 16}, {42, 2}, {-42, 2},
        {100, 8}, {-100, 8}, {123, 10}, {-123, 10},
        {1000, 36}, {-1000, 36}, {0, 16}, {0, 2},
        {INT_MAX, 16}, {INT_MIN, 16}
    };
    
    for (int i = 0; i < sizeof(base_tests)/sizeof(base_tests[0]); i++) {
        oversprintf(buffer, "%d base %d -> %%Cv: %Cv", 
                   base_tests[i].num, base_tests[i].base, 
                   base_tests[i].num, base_tests[i].base);
        printf("%s\n", buffer);
        
        oversprintf(buffer, "%d base %d -> %%CV: %CV", 
                   base_tests[i].num, base_tests[i].base, 
                   base_tests[i].num, base_tests[i].base);
        printf("%s\n", buffer);
    }
    
    printf("\n--- %%to и %%TO (перевод в десятичную) ---\n");
    struct convert_test {
        char *str;
        int base;
    } convert_tests[] = {
        {"ff", 16}, {"FF", 16}, {"1010", 2}, {"-1010", 2},
        {"144", 8}, {"-144", 8}, {"z", 36}, {"Z", 36},
        {"1a", 16}, {"1A", 16}, {"0", 16}, {"0", 2},
        {"7fffffff", 16}, {"-80000000", 16}
    };
    
    for (int i = 0; i < sizeof(convert_tests)/sizeof(convert_tests[0]); i++) {
        oversprintf(buffer, "\"%s\" base %d -> %%to: %to", 
                   convert_tests[i].str, convert_tests[i].base,
                   convert_tests[i].str, convert_tests[i].base);
        printf("%s\n", buffer);
        
        oversprintf(buffer, "\"%s\" base %d -> %%TO: %TO", 
                   convert_tests[i].str, convert_tests[i].base,
                   convert_tests[i].str, convert_tests[i].base);
        printf("%s\n", buffer);
    }
    
    printf("\n--- Дампы памяти ---\n");
    
    printf("--- %%mi (int) ---\n");
    int int_tests[] = {0, 1, -1, 42, -42, 255, -255, 0x12345678, -0x12345678, INT_MAX, INT_MIN};
    for (int i = 0; i < sizeof(int_tests)/sizeof(int_tests[0]); i++) {
        oversprintf(buffer, "%d (0x%x) -> %%mi: %mi", 
                   int_tests[i], int_tests[i], int_tests[i]);
        printf("%s\n", buffer);
    }
    
    printf("\n--- %%mu (unsigned int) ---\n");
    unsigned int uint_tests[] = {0, 1, 42, 255, 0xABCD1234, 0xFFFFFFFF, UINT_MAX};
    for (int i = 0; i < sizeof(uint_tests)/sizeof(uint_tests[0]); i++) {
        oversprintf(buffer, "%u (0x%x) -> %%mu: %mu", 
                   uint_tests[i], uint_tests[i], uint_tests[i]);
        printf("%s\n", buffer);
    }
    
    printf("\n--- %%mf (float) ---\n");
    float float_tests[] = {0.0f, 1.0f, -1.0f, 3.14159f, -2.71828f, 
                          FLT_MAX, FLT_MIN, FLT_EPSILON, -FLT_MAX};
    for (int i = 0; i < sizeof(float_tests)/sizeof(float_tests[0]); i++) {
        oversprintf(buffer, "%f -> %%mf: %mf", float_tests[i], float_tests[i]);
        printf("%s\n", buffer);
    }
    
    printf("\n--- %%md (double) ---\n");
    double double_tests[] = {0.0, 1.0, -1.0, 3.141592653589793, -2.718281828459045,
                           DBL_MAX, DBL_MIN, DBL_EPSILON, -DBL_MAX};
    for (int i = 0; i < sizeof(double_tests)/sizeof(double_tests[0]); i++) {
        oversprintf(buffer, "%f -> %%md: %md", double_tests[i], double_tests[i]);
        printf("%s\n", buffer);
    }
    
    printf("\n=== ТЕСТ 3: КОРНЕРНЫЕ СЛУЧАИ И МУСОР ===\n");
    
    printf("--- Некорректные основания систем счисления ---\n");
    overfprintf(stdout, "Base 0 -> %%Cv: %Cv\n", 255, 0);
    overfprintf(stdout, "Base 1 -> %%Cv: %Cv\n", 255, 1);
    overfprintf(stdout, "Base 37 -> %%Cv: %Cv\n", 255, 37);
    overfprintf(stdout, "Base -10 -> %%Cv: %Cv\n", 255, -10);
    overfprintf(stdout, "Base 100 -> %%Cv: %Cv\n", 255, 100);
    
    printf("\n--- Некорректные строки для преобразования ---\n");
    overfprintf(stdout, "Пустая строка -> %%to: %to\n", "", 16);
    overfprintf(stdout, "NULL строка -> %%to: %to\n", NULL, 16);
    overfprintf(stdout, "Некорректные символы -> %%to: %to\n", "hello!", 10);
    overfprintf(stdout, "Символы вне base -> %%to: %to\n", "123z", 10);
    overfprintf(stdout, "Только минус -> %%to: %to\n", "-", 10);
    
    printf("\n--- Граничные значения ---\n");
    overfprintf(stdout, "INT_MAX римские: %Ro\n", INT_MAX);
    overfprintf(stdout, "INT_MIN римские: %Ro\n", INT_MIN);
    overfprintf(stdout, "UINT_MAX цекендорф: %Zr\n", UINT_MAX);
    overfprintf(stdout, "INT_MAX в base 2: %Cv\n", INT_MAX, 2);
    overfprintf(stdout, "INT_MIN в base 2: %Cv\n", INT_MIN, 2);
    
    printf("\n--- Специальные вещественные значения ---\n");
    overfprintf(stdout, "NaN float -> %%mf: %mf\n", 0.0f/0.0f);
    overfprintf(stdout, "Infinity float -> %%mf: %mf\n", 1.0f/0.0f);
    overfprintf(stdout, "-Infinity float -> %%mf: %mf\n", -1.0f/0.0f);
    overfprintf(stdout, "NaN double -> %%md: %md\n", 0.0/0.0);
    overfprintf(stdout, "Infinity double -> %%md: %md\n", 1.0/0.0);
    overfprintf(stdout, "-Infinity double -> %%md: %md\n", -1.0/0.0);
    
    printf("\n=== ТЕСТ 4: КОМБИНАЦИИ И СЛОЖНЫЕ ФОРМАТЫ ===\n");
    
    printf("--- Комбинации стандартных и кастомных ---\n");
    oversprintf(buffer, "Число: %d, Римское: %Ro, В 16-ной: %Cv, Цекендорф: %Zr", 
               42, 42, 42, 16, 10U);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Строка: %s, Число: %d -> base2: %Cv, Память: %mi", 
               "test", 255, 255, 2, 255);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Float: %.2f -> память: %mf, Double: %f -> память: %md", 
               3.14f, 3.14f, 2.71828, 2.71828);
    printf("%s\n", buffer);
    
    printf("\n--- Множественные вхождения ---\n");
    oversprintf(buffer, "%Ro %Ro %Ro %Ro %Ro", 1, 4, 9, 42, 1999);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "%Cv %Cv %Cv %Cv", 255, 16, 42, 2, 100, 8, 1000, 36);
    printf("%s\n", buffer);
    
    printf("\n--- Сложные форматы с шириной и точностью ---\n");
    oversprintf(buffer, "|%10Ro| |%-10Ro|", 42, 42);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "|%20Cv| |%-20Cv|", 255, 16, 255, 16);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "|%30Zr| |%-30Zr|", 10U, 10U);
    printf("%s\n", buffer);
    
    printf("\n=== ТЕСТ 5: ПРОВЕРКА ПЕРЕПОЛНЕНИЯ БУФЕРА ===\n");
    
    char small_buffer[10];
    int small_written = oversprintf(small_buffer, "%Ro", 1999);
    printf("Записано в малый буфер: %d, содержимое: '%s'\n", small_written, small_buffer);
    
    small_written = oversprintf(small_buffer, "%Cv", 123456789, 16);
    printf("Записано в малый буфер: %d, содержимое: '%s'\n", small_written, small_buffer);
    
    printf("\n=== ТЕСТ 6: ПРОВЕРКА ВОЗВРАЩАЕМОГО ЗНАЧЕНИЯ ===\n");
    
    int written;
    written = overfprintf(stdout, "Тест возврата: %d %s %Ro\n", 42, "hello", 1999);
    printf("Возвращено: %d\n", written);
    
    written = oversprintf(buffer, "Тест возврата: %d %s %Ro", 42, "hello", 1999);
    printf("Возвращено: %d, строка: '%s'\n", written, buffer);
    
    printf("\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n");
    
    return 0;
}