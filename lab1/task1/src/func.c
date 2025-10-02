#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/func.h"
#include "../include/utils.h"

int* func_a(const int x, int*length)
{
    int* result = malloc(sizeof(int) * 100);
    if (!result) return NULL;
    if (x>50 || x<-50) {
        free(result);
        return NULL;
    }
    
    int i = 0, k = 2;
    if (x >= 0) {
        while(k*x <= 100) {
            result[i] = k*x;
            ++i;
            ++k;
        }
    } else {
        k = -2;
        while(k*x <= 100) {
            result[i] = k*x;
            ++i;
            --k;
        }
    }
    *length = i;  
    return result;
}
int func_b(const int x)
{
    int result = is_simple(x);
    return result;
}
int * func_c(const int x, int*len)
{   
    int *result = int_to_hex(x, len);
    return result;

}
void func_d(const int x)
{
    int i = 1;
    while (i<=10){
        fprintf(stdout, "%d   ", i*x);
        ++i;
    }
    fprintf(stdout, "\n");
}
long long func_f (const int x)
{
    long long result = factorial(x);
    return result;
}
int func_e(const int x)
{
    int result = sum(x);
    return result;
}