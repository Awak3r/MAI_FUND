#include <unistd.h>
#include <stdlib.h>
#include "../include/utils.h"


long long  factorial (const int x){
    if (x<0 || x>20) return -1;
    long long  n=1;
    for (int i=2; i<=x; i++){
        n*=i;
    }
    return n;
}

int sum(const int x){
    if (x<0) return -1;
    int n=0;
    for (int i=0; i<=x; i++){
        n+=i;
    }
    return n;
}

int is_simple(const int x){
{   if (x<2) return 0;
    if (x==2) return 1;
    if (x%2==0) return 0;
    for (int i=3; i*i<=x; i+=2){
        if (x%i==0){
            return 0;
        }
    }
    return 1;
}
}

int* int_to_hex(int x, int* len) {
    int *result = malloc(sizeof(int) * 16);
    if (!result) return NULL;
    int i = 0;
    if (x ==0){
        result[0] = 0;
        *len = 1;
        return result;
    }
    while (x > 0) {
        result[i] = x % 16;
        ++i;
        x /= 16;
    }
    *len = i;
    return result;
}


