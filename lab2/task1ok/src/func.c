#include "../include/func.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
void v_prime(long long n, int factors[], int *count) {
    *count = 0;
    if (n % 2 == 0) {
        factors[(*count)++] = 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors[(*count)++] = i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors[(*count)++] = n;
    }
}

long long NOD(long long a1, long long b1){
    long long a = a1, b= b1;
    long long r = 1, NOD;
    while(r){
        r = a%b;
        if (r == 0) 
        {
            NOD = b;
            break;
        }
        a = b;
        b = r;
    }
    return NOD;
}

int test (double num, int base){
    long long znam = 1;
    int obrez = 0;
    while (fmod(num,1) > 1e-9 && obrez<=15) {
        num*=10;
        znam*=10;
        obrez++;
    }
    long long num1 = (long long)(num + 0.5);
    long long N = NOD(num1,znam);
    znam/=N;
    int count1, count2, flag = 0;
    int f1[256], f2[256];
    v_prime(znam, f1, &count1);
    v_prime(base, f2, &count2);
    for(int i = 0; i<count1; i++){
        for (int j = 0; j<count2; j++){
            if (f1[i]==f2[j]) flag = 1;
        }

        if (!flag) {
            return 0;
        }
        flag = 0;

    }
    
    return 1;
}

void func(int base, int count, ...){
    va_list args;
    va_start(args, count);
    double num;
    int cur, k = 0;
    if (base < 2){
        fprintf(stderr, "error: num must be in [0,1]\n");
    } else {
        for(int i = 1; i<=count; i++){
            num = va_arg(args, double);
            if (num <= 0 || num >= 1) fprintf(stderr, "error: num must be in [0,1]\n");
            continue;
            cur = test(num, base);
            if (cur) fprintf(stdout, "%d) yes  ", i);
            else fprintf(stdout, "%d) no   ", i);
        }
        fprintf(stdout, "\n");
        va_end(args);
    }   
}