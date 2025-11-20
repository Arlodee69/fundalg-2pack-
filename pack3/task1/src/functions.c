#include "../include/header.h"

status convert(const int number, const int r, char* output) {
    if (!output || r < 1 || r > 5) {
        return INVALID_INPUT;
    }

    if (number == 0) {
        output[0] = '0';
        output[1] = '\0';
        return VALID;
    }

    const char nums[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int tmp = number;
    int isNeg = 0;

    if (tmp < 0) {
        isNeg = 1;
        tmp = ~tmp;
        tmp = sumOne(tmp);
    }

    unsigned int mask = 1u;
    mask = mask << r;
    mask = subtractOne(mask);

    char temp[BUFSIZ];
    unsigned int idx = BUFSIZ;
    idx = subtractOne(idx);
    temp[idx] = '\0';


    while (tmp != 0 && idx != 0) {

        idx = subtractOne(idx);
        unsigned int remains = tmp & mask;
        temp[idx] = nums[remains];
        tmp = tmp >> r;
    }

    if (isNeg && idx != 0) {
        idx = subtractOne(idx);
        temp[idx] = '-';
    }

    unsigned int outpos = 0;

    while (temp[idx] != '\0') {
        output[outpos] = temp[idx];
        outpos = sumOne(outpos);
        idx = sumOne(idx);
    }

    output[outpos] = '\0';
    return VALID;
}

unsigned int sumOne(unsigned int a) {
    unsigned int one = 1;

    while (one) {
        unsigned int carry = a & one;
        a = a ^ one;
        one = carry << 1;
    }

    return a;
}

unsigned int subtractOne(unsigned int a) {
    unsigned int one = 1;

    while (one) {
        unsigned int carry = (~a) & one;
        a =  a ^ one;
        one = carry << 1;
    }

    return a;
}