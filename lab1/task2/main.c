#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/func.h"
#include <limits.h>

int main()
{   
    int count, cur_n, res_n;
    int * simple = simple_numbers(&count);
    if (simple == NULL){
        fprintf(stderr, "error: cant make list of primes\n");
        free(simple);
        return -1;
    }
    int len = read_number();
    if (len < 1){
        fprintf(stderr, "error: cant read from stdin\n");
        free(simple);
        return -1;
    }
    for (int i=0;i<len;i++){
        cur_n = read_number();
        if (cur_n < 1){
            fprintf(stderr, "error: cant read from stdin\n");
            free(simple);
            return -1;
        }
        if (cur_n<=count){
        res_n  = task2(simple, cur_n);
        printf("%d\n", res_n);
        }else{
            fprintf(stderr, "error: so large number (if u want number larger change max_int from 10^8 to INT_MAX) GL.\n");
            return -1;
        }
    }
    free(simple);
}
