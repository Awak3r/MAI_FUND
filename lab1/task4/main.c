#include <stdio.h>
#include <stdlib.h>
#include "include/func.h"

int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "error: invalid input\n");
        return -1;
    }
    
    double epsilon = atof(argv[1]);
    if (epsilon<0){
        fprintf(stderr, "error: invalid epsilon\n");
        return -1;
    }
    if (epsilon< 0.00000001){
        fprintf(stderr, "so small eps (max = 0.00000001)\n");
        return -1;
    }
    fprintf(stdout, "e:\n");
    double e_a = calculate_e_a(epsilon);
    double e_b = calculate_e_b(epsilon);
    double e_c= calculate_e_c(epsilon);
    fprintf(stdout, "limit:    %.10f\n", e_a);
    fprintf(stdout, "series:   %.10f\n", e_b);
    fprintf(stdout, "equation: %.10f\n\n", e_c);
    fprintf(stdout, "π:\n");
    double pi_a = calculate_pi_a(epsilon);
    double pi_b = calculate_pi_b(epsilon);
    double pi_c = calculate_pi_c(epsilon);
    fprintf(stdout, "limit:    %.10f\n", pi_a);
    fprintf(stdout, "series:   %.10f\n", pi_b);
    fprintf(stdout, "equation: %.10f\n\n", pi_c);
    fprintf(stdout, "ln(2):\n");
    double ln2_a = calculate_ln2_a(epsilon);
    double ln2_b = calculate_ln2_b(epsilon);
    double ln2_c = calculate_ln2_c(epsilon);
    fprintf(stdout, "limit:    %.10f\n", ln2_a);
    fprintf(stdout, "series:   %.10f\n", ln2_b);
    fprintf(stdout, "equation: %.10f\n\n", ln2_c);
    fprintf(stdout, "sqrt(2):\n");
    double sqrt2_a = calculate_sqrt2_a(epsilon);
    double sqrt2_b = calculate_sqrt2_b(epsilon);
    double sqrt2_c = calculate_sqrt2_c(epsilon);
    fprintf(stdout, "limit:    %.10f\n", sqrt2_a);
    fprintf(stdout, "series:   %.10f\n", sqrt2_b);
    fprintf(stdout, "equation: %.10f\n\n", sqrt2_c);
    fprintf(stdout, "y:\n");
    double gamma_a = calculate_gamma_a(epsilon);
    double gamma_b = calculate_gamma_b(epsilon);
    double gamma_c = calculate_gamma_c(epsilon);
    fprintf(stdout, "limit:    %.10f\n", gamma_a);
    fprintf(stdout, "series:   %.10f\n", gamma_b);
    fprintf(stdout, "equation: %.10f\n\n", gamma_c);
    
    return 0;
}