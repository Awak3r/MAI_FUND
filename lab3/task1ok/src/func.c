#include "../include/func.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//https://habr.com/ru/articles/444550/
unsigned int difference(unsigned int a, unsigned int b){
    while (b != 0) {
        unsigned int bor = ~a&b;
        a= a^b;
        b = bor<<1;
    }
    return a;
}

unsigned int add_1(unsigned int a) {
    unsigned int carry = 1;
    while (carry != 0) {
        unsigned int temp_carry = a & carry; 
        a = a ^ carry;                        
        carry = temp_carry << 1;              
    }
    return a;
}

unsigned int del(unsigned int a, unsigned int b, unsigned int * ostatok){
    int a_cur = a, b_cur = b;
    unsigned int res = 0;
    if (a == 0){
        *ostatok = 0;
        return 0;
    }
    if (b == 0){
        *ostatok = 0;
        return (unsigned int)(-1);
    }
    if (b>a){
        *ostatok = a;
        return 0;
    }

    while ((b_cur<<1) <=a && ((b_cur & (1U<<31)) == 0)) {
        b_cur= b_cur<<1;
    }
    while (b_cur >= b) {
        if (a_cur>=b_cur){
            a_cur = difference(a_cur, b_cur);
            res = res<<1 | 1;
        } else{
            res = res<<1;
        }
        b_cur = b_cur >> 1;
    }
    *ostatok = a_cur;
    return res;
}


char * func(int num, int base){
    switch (base) {
        case 1: base = 2;
        break;
        case 2: base = 4;
        break;
        case 3: base = 8;
        break;
        case 4: base = 16;
        break;
        case 5: base = 32;
        break;
        default: return NULL;
    }
    char * digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *res1 = malloc(sizeof(char) * 100);
    char *res2 = malloc(sizeof(char) * 100);
    unsigned int ostatok;
    if (!res1 || !res2) {
        free(res1);
        free(res2);
        return NULL;
    }
    if (num == 0) {
        strcpy(res2, "0");
        free(res1);
        return res2;
    }
    int flag = 0;
    if (num < 0){
        flag = 1;
        num = add_1(~num);
    }
    int i = 0, k = 0;
    while (num>0) {
        num = del(num, base, &ostatok);
        res1[i] = digits[ostatok]; 
        i = add_1(i);
    }
    if (flag == 1) {
        res1[i] = '-';
        i = add_1(i);
    }
    i = difference(i, 1);
    while (i>=0) {
        res2[k] = res1[i];
        k = add_1(k);
        i = difference(i, 1);
    }
    res2[k] = '\0';
    free(res1);
    return res2;
}