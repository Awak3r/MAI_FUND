#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/func.h"


int main()
{
    int count, cur_n, res_n;
    int * simple = simple_numbers(&count);
    if (simple == NULL){
        const char msg[] = "error: cant make list of primes";
        fprintf(stderr, msg);
        free(simple);
        exit(EXIT_FAILURE);
    }
    int len = read_number();
    if (len == -1){
        const char msg[] = "error: cant read from stdin";
        fprintf(stderr, msg);
        free(simple);
        exit(EXIT_FAILURE);
    }
    else if (len < 1){
        const char msg[] = "error: cant read from stdin";
        fprintf(stderr, msg);
        free(simple);
        exit(EXIT_FAILURE);
    }
    for (int i=0;i<len;i++){
        cur_n = read_number();
        if (cur_n == -1){
            const char msg[] = "error: cant read from stdin";
            fprintf(stderr, msg);
            free(simple);
            exit(EXIT_FAILURE);
        }
        res_n  = task2(simple, cur_n);
        printf("%d\n", res_n);
    }
    free(simple);
}
