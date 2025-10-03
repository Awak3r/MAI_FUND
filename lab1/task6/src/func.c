#include "../include/func.h"
#include <math.h>


double func_a(double x, double epsilon){
    //ln(1+x)/x
    if (fabs(x)<epsilon){
        return 1;
    }
    return (log(x+1)/x);
}

double func_b(double x, double epsilon){
    //e^(-x^/2)
    return exp((-x*x)/2);
}
double func_c(double x, double epsilon){
    //ln(1/(1-x))
    if (fabs(1.0 - x) < epsilon){
        return log(1/(1-x+epsilon));
    }
    return -log(1-x);
}

double  func_d(double x, double epsilon){
    if (fabs(x) < epsilon){
        return 1;
    }
    return pow(x, x);
}

double integral(double epsilon, char var){
    double a = 0, b = 1;
    int n = 1;
    double h = b - a;
    double integral_old;
    double integral_new;
    if (var == 'a') integral_old = (func_a(a, epsilon) + func_a(b, epsilon)) * h / 2;
    if (var == 'b') integral_old = (func_b(a, epsilon) + func_b(b, epsilon)) * h / 2;
    if (var == 'c') integral_old = (func_c(a, epsilon) + func_c(b, epsilon)) * h / 2;
    if (var == 'd') integral_old = (func_d(a, epsilon) + func_d(b, epsilon)) * h / 2;
    for (int i = 1; i<10000; i++){
        n*=2;
        h/=2;
        integral_new = integral_old / 2;
        for (int k = 1; k<n; k+=2){
            if (var == 'a') integral_new += func_a(a + (k*h), epsilon) * h;
            if (var == 'b') integral_new += func_b(a + (k*h), epsilon) * h;
            if (var == 'c') integral_new += func_c(a + (k*h), epsilon) * h;
            if (var == 'd') integral_new += func_d(a + (k*h), epsilon) * h;
        }
        if (fabs(integral_new - integral_old) < epsilon){
            return integral_new;
        }
        integral_old = integral_new;
    }
    return integral_new;
}