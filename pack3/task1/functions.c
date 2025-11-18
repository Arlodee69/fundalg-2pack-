#include "header.h"

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

status convert(const unsigned int number, const int r, char* output) {
    if (!output || r < 1 || r > 5) {
        return INVALID_INPUT;
    }

    unsigned int tmpnumber = number;

    if (tmpnumber == 0) {
        output[0] = '0';
        output[1] = '\0';
        return VALID;
    }
    
    const unsigned int max = 32;
    char temp_result[33];

    for (unsigned int i = 0; i < 33; i = sumOne(i)) {
        temp_result[i] = '0';
    }

    temp_result[32] = '\0';

    const char nums[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int mask = subtractOne(1 << r);
    unsigned int index = subtractOne(max);
    unsigned int remains = 0;

    while (tmpnumber != 0) {
        remains = tmpnumber & mask;
        temp_result[index] = nums[remains];
        index = subtractOne(index);
        tmpnumber = tmpnumber >> r;
    }

    unsigned int startPos = 0;
    while (temp_result[startPos] == '0' && startPos != subtractOne(max)) {
        startPos = sumOne(startPos);
    }

    unsigned int newPos = 0;
    unsigned int currPos = startPos;
    
    while (temp_result[currPos] != '\0') {
        output[newPos] = temp_result[currPos];
        newPos = sumOne(newPos);
        currPos = sumOne(currPos);
    }
    output[newPos] = '\0';

    return VALID;
}