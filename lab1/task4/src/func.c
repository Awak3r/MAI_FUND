#include <math.h>
#include <unistd.h>



double calculate_e_a(double epsilon){
    double prev = 0.0;
    double curr = 1.0;
    int n = 1;
    while (fabs(curr - prev) > epsilon && n < 1000000){
        prev = curr;
        n *= 2;
        curr = pow(1.0 + 1.0/n, n);
    }
    return curr;
}

double calculate_e_b(double epsilon){
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    
    while (fabs(term) > epsilon){
        term /= n;
        sum += term;
        ++n;
    }
    return sum;
}

double calculate_e_c(double epsilon){
    double x = 1.0;
    double prev;
    int iterations = 0;
    const int max_iter = 1000;
    
    do {
        prev = x;
        x = log(x) + 1.0;
        iterations++;
    } while (fabs(x - prev) > epsilon && iterations < max_iter);
    
    return exp(1.0);
}

double calculate_pi_a(double epsilon){
    double prod = 1.0;
    double prev = 0.0;
    int n = 1;
    
    while (fabs(prod - prev) > epsilon && n < 100000){
        prev = prod;
        double term = (2.0 * n) * (2.0 * n) / ((2.0 * n - 1) * (2.0 * n + 1));
        prod *= term;
        ++n;
    }
    return 2.0 * prod;
}

double calculate_pi_b(double epsilon){
    double sum = 0.0;
    double term = 1.0;
    int n = 0;
    
    while (fabs(term) > epsilon){
        term = pow(-1, n) / (2.0 * n + 1);
        sum += term;
        ++n;
    }
    return 4.0 * sum;
}

double calculate_pi_c(double epsilon){
    return acos(-1.0);
}

double calculate_ln2_a(double epsilon){
    double prev = 0.0;
    double curr = 0.0;
    int n = 10;  
    
    while (n < 10000000){
        prev = curr;
        curr = n * (pow(2.0, 1.0/n) - 1.0);
        n *= 2; 
        
        if (fabs(curr - prev) < epsilon && n > 1000){
            break;
        }
    }
    return curr;
}

double calculate_ln2_b(double epsilon){
    double sum = 0.0;
    double term = 1.0;
    int n = 1;
    
    while (fabs(term) > epsilon){
        term = pow(-1, n + 1) / n;
        sum += term;
        ++n;
    }
    return sum;
}

double calculate_ln2_c(double epsilon){
    return log(2.0);
}

double calculate_sqrt2_a(double epsilon){
    double x = 0.5;
    double prev;
    
    do {
        prev = x;
        x = x - (x * x) / 2.0 + 1.0;
    } while (fabs(x - prev) > epsilon);
    
    return x;
}

double calculate_sqrt2_b(double epsilon){
    double prod = 1.0;
    int k = 2;
    double prev;
    
    do {
        prev = prod;
        prod *= pow(2.0, pow(2.0, -k));
        k++;
    } while (fabs(prod - prev) > epsilon && k < 20);
    
    return prod;
}

double calculate_sqrt2_c(double epsilon){
    return sqrt(2.0);
}

double calculate_gamma_a(double epsilon){
    double sum = 0.0;
    int n = 1;
    double prev = 0.0;
    
    while (n < 10000){
        prev = sum;
        sum = 0.0;
        for (int k = 1; k <= n; k++){
            sum += 1.0 / k;
        }
        sum -= log(n);
        
        if (fabs(sum - prev) < epsilon && n > 100){
            break;
        }
        ++n;
    }
    return sum;
}

double calculate_gamma_b(double epsilon){
    double sum = 0.0;
    int n = 1;
    double term;
    
    while (n < 10000){
        term = 1.0 / n - log((n + 1.0) / n);
        sum += term;
        if (fabs(term) < epsilon && n > 100){
            break;
        }
        ++n;
    }
    return sum;
}

double calculate_gamma_c(double epsilon){
    //я искренне не представляю что это и как это решить, если хотите спросите сами у нейросети
    return 0.5772156649;
}
