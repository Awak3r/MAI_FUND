#include "include/func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "error: invalid input\n");
        return -1;
    }
    
    double epsilon = atof(argv[1]);
    
    printf("Epsilon = %.15f\n\n", epsilon);
    
    printf("e (метод a): %.15f\n", calculate_e_a(epsilon));
    printf("e (метод b): %.15f\n", calculate_e_b(epsilon));
    printf("e (метод c): %.15f\n", calculate_e_c(epsilon));
    printf("e (эталон):  %.15f\n\n", M_E);
    
    printf("π (метод a): %.15f\n", calculate_pi_a(epsilon));
    printf("π (метод b): %.15f\n", calculate_pi_b(epsilon));
    printf("π (метод c): %.15f\n", calculate_pi_c(epsilon));
    printf("π (эталон):  %.15f\n\n", M_PI);
    
    printf("ln2 (метод a): %.15f\n", calculate_ln2_a(epsilon));
    printf("ln2 (метод b): %.15f\n", calculate_ln2_b(epsilon));
    printf("ln2 (метод c): %.15f\n", calculate_ln2_c(epsilon));
    printf("ln2 (эталон):  %.15f\n\n", M_LN2);
    
    printf("√2 (метод a): %.15f\n", calculate_sqrt2_a(epsilon));
    printf("√2 (метод b): %.15f\n", calculate_sqrt2_b(epsilon));
    printf("√2 (метод c): %.15f\n", calculate_sqrt2_c(epsilon));
    printf("√2 (эталон):  %.15f\n\n", M_SQRT2);
    
    printf("γ (метод a): %.15f\n", calculate_gamma_a(epsilon));
    printf("γ (метод b): %.15f\n", calculate_gamma_b(epsilon));
    printf("γ (метод c): %.15f\n", calculate_gamma_c(epsilon));
    
    return 0;
}