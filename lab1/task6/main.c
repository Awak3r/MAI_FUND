#include "include/func.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    if (argc != 2){
        fprintf(stdout, "error: invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    float epsilon = (double)atof(argv[1]);
    double result_a = integral(epsilon, 'a');
    double result_b = integral(epsilon, 'b');
    double result_c = integral(epsilon, 'c');
    double result_d = integral(epsilon, 'd');
    fprintf(stdout, "result (a): %f\n", result_a);
    fprintf(stdout, "result (b): %f\n", result_b);
    fprintf(stdout, "result (c): %f\n", result_c);
    fprintf(stdout, "result (d): %f\n", result_d);
    
}
