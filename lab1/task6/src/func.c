#include "../include/func.h"
#include <math.h>
#include <sys/types.h>




double func(double x, double epsilon,char var){
    
    switch (var) {
    case('a'): {
    //ln(1+x)/x
    if (fabs(x)<epsilon){
        return 1;
    }
    return (log(x+1)/x); }
    case('b'): {
    //e^(-x^/2)
    return exp((-x*x)/2); }
    case('c'): {
    //ln(1/(1-x))
    if (fabs(1.0 - x) < epsilon){
        return log(1/(1-x+epsilon));
    }
    return -log(1-x); }
    case('d'): {
    //x^x
    if (fabs(x) < epsilon){
        return 1;
    }
    return pow(x, x);
    }
    default: return -1;
}
}

int n_for_epsilon(double epsilon, char var){
    double E;
    int n = 2;
    double second_p;
    switch (var) {
        case('a'): second_p = 198.88;
        break;
        case('b'): second_p = 1;
        break;
        case('c'): second_p = 198.38;
        break;
        case('d'): second_p = 9.29;
        break;
    }
    while (1) {
        E=1.0/(12*pow(n, 2))*second_p;
        if(E<=epsilon){
            return n;
        }
        n*=2;
    }
}



double integral(double epsilon, char var){
    int n = n_for_epsilon(epsilon, var);
    double I = 0, h = 1.0/n;
    for (double i=0; i<1; i+=h) {
    I+=h/2*(func(i,epsilon, var) + func(i+h,epsilon, var));
    }
    return I;

}