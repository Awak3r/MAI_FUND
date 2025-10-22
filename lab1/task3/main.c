#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/func.h"
#include "include/utils.h"


int main(int argc, char **argv)
{
    if (argc <2){
        fprintf(stderr, "error: incorect arguments\n");
        return -1;
    }
    if ((argv[1][0] != '-' && argv[1][0] != '/') && (argv[1][1] != 'q' && argv[1][1] != 'm' && argv[1][1] != 't')){
        fprintf(stderr, "error: incorect arguments\n");
        return -1;
    }
    char flag = argv[1][1];
    int result1;
    int length = 0;
    float epsilon;
    float coef[3];
    switch (flag) {
    case 'q':
        if (argc != 6){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        if (!(is_number(argv[2]) && is_number(argv[3]) && is_number(argv[4]) && is_number(argv[5]))){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        epsilon = atof(argv[2]);
        coef[0] = atof(argv[3]);
        coef[1] = atof(argv[4]);
        coef[2] = atof(argv[5]);
        func_a(epsilon, coef, &length);
    break;
    case 'm':
        if (argc != 4){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        if (!(is_number(argv[2]) && is_number(argv[3]))){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        const int x1 = atof(argv[2]);
        const int x2 = atof(argv[3]);
        if ((int)x1 != x1 || (int)x2 != x2){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        result1 = func_b((int)x1, (int)x2);
        if (result1 == 1){
            fprintf(stdout, "is multiple\n");
        }
        else {
            fprintf(stdout, "isn't multiple\n");
        }
    break;
    case 't':
        if (argc != 6){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        if (!(is_number(argv[2]) && is_number(argv[3]) && is_number(argv[4]) && is_number(argv[5]))){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        epsilon = atof(argv[2]);
        coef[0] = atof(argv[3]);
        coef[1] = atof(argv[4]);
        coef[2] = atof(argv[5]);
        if(coef[0]< 0 ||  coef[1] < 0 || coef[2] < 0){
            fprintf(stderr, "error: incorect arguments\n");
            return -1;
        }
        result1 = func_c(epsilon, coef);
        if (result1 == 1){
            fprintf(stdout, "can be right triangle\n");
        }
        else{
            fprintf(stdout, "can't be right triangle\n");
        }
    break;
    }   
}
