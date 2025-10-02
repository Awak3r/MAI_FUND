#include <stdio.h>
#include <stdlib.h>
#include "../include/func.h"
#include "../include/utils.h"

void func_a(float epsilon, float coef[3], int * length){
    float * res;
    int i = 0;
    if (epsilon <= 0){
        fprintf(stderr, "error: incorect arguments\n");
        exit(EXIT_FAILURE);
    }
    float processed[6][3];
    int processed_count = 0;
    int permutations[6][3] = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 0, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0}
        };
    int k;
    for (k = 0; k < 6; k++){
        const float a = coef[permutations[k][0]];
        const float b = coef[permutations[k][1]];
        const float c = coef[permutations[k][2]];
        if (is_permutation_unique(processed, processed_count, a, b, c, epsilon)){
            res = uravn(a, b, c, epsilon, length);
            if (*length == 0){
                fprintf(stdout, "no solutions\n");
                free(res);
                continue;
            }
            if (*length == -1){
                fprintf(stdout, "all numbers - solution\n");
                free(res);
                continue;
            }
            for (int j = 0; j< *length; j++){
              fprintf(stdout, "%f", res[j]);
            }
            fprintf(stdout, "\n");
            processed[processed_count][0] = a;
            processed[processed_count][1] = b;
            processed[processed_count][2] = c;
            processed_count++;
            free(res);
        }
    }
}

int func_b(const int x1, const int x2){
    if ((x1 == 0 || x2 == 0)){
        return -1;
    }
    if (x1%x2 == 0) return 1;
    return 0;
}

int func_c(const float epsilon, float coef[3]){
    if(tupoi_epsilon((coef[0]*coef[0] + coef[1]*coef[1]), coef[2]*coef[2], epsilon) || \
       tupoi_epsilon((coef[1]*coef[1] + coef[2]*coef[2]), coef[0]*coef[0], epsilon) || \
       tupoi_epsilon((coef[2]*coef[2] + coef[0]*coef[0]), coef[1]*coef[1], epsilon)){
        return 1;
       }
    else {
        return 0;
    }
}
