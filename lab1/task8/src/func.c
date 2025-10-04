#include "../include/func.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int test_in(char * string, int n){
    int i = 0;
    if (string[0] == '-'){
        ++i;
    }
    if (string[i] == '\0' || string[i] == '\n') {
        return 0;
    }
 while (string[i] != '\0' && string[i] != '\n') {
        if (!((string[i] >= '0' && string[i] <= '9') || 
        (toupper(string[i]) >= 'A' && (toupper(string[i]) - 'A' + 10) < n))) {
            return 0;
        }
    ++i;
    }
    return 1;
}

long in_to_10number(char * string, int n){
    long number  = strtol(string, NULL,n);
    return number;
}

void convert_to_n(int number, int base, char *result){
    if (number == 0){
        strcpy(result, "0");
        return;
    }
    int is_negative = 0;
    if (number < 0){
        is_negative = 1;
        number = -number;
    }
    char temp[100];
    int i = 0;
    while (number > 0){
        int digit = number % base;
        if (digit < 10){
            temp[i++] = '0' + digit;
        } else {
            temp[i++] = 'A' + (digit - 10);
        }
        number /= base;
    }
    int j = 0;
    if (is_negative){
        result[j++] = '-';
    }
    while (i > 0){
        result[j++] = temp[--i];
    }
    result[j] = '\0';
}
