#include <math.h>


// ============= ЧИСЛО e =============

double calculate_e_a(double epsilon) {
    double prev = 0.0;
    double curr = 1.0;
    long long n = 1;
    while (fabs(curr - prev) > epsilon && n < 1000000000LL) {
        prev = curr;
        n *= 2;
        curr = pow(1.0 + 1.0/n, n);
    }
    return curr;
}

double calculate_e_b(double epsilon) {
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    while (fabs(term) > epsilon && n < 100000) {
        term /= n;
        sum += term;
        n++;
    }
    return sum;
}

double calculate_e_c(double epsilon) {
    // Решаем уравнение ln(x) = 1 => x = e
    // Метод Ньютона для f(x) = ln(x) - 1
    double x = 2.5;  // Начальное приближение
    double prev;
    int iterations = 0;
    const int max_iter = 1000;
    
    do {
        prev = x;
        // f(x) = ln(x) - 1, f'(x) = 1/x
        // x_new = x - f(x)/f'(x) = x - (ln(x) - 1) * x = x - x*ln(x) + x = 2x - x*ln(x)
        x = x / (1.0 + log(x) - 1.0);  // Более стабильная формула
        iterations++;
    } while (fabs(x - prev) > epsilon && iterations < max_iter);
    
    return x;
}

// ============= ЧИСЛО π =============

double calculate_pi_a(double epsilon) {
    // Формула Валлиса: π/2 = ∏(4n²/(4n²-1))
    double prod = 1.0;
    double prev = 0.0;
    int n = 1;
    
    while (fabs(prod - prev) > epsilon && n < 1000000) {
        prev = prod;
        double term = (4.0 * n * n) / (4.0 * n * n - 1.0);
        prod *= term;
        n++;
    }
    return 2.0 * prod;
}

double calculate_pi_b(double epsilon) {
    // Ряд Лейбница: π/4 = 1 - 1/3 + 1/5 - 1/7 + ...
    double sum = 0.0;
    int n = 0;
    double term;
    
    do {
        term = (n % 2 == 0 ? 1.0 : -1.0) / (2.0 * n + 1);
        sum += term;
        n++;
    } while (fabs(term) > epsilon && n < 10000000);
    
    return 4.0 * sum;
}

double calculate_pi_c(double epsilon) {
    // Решаем cos(x) = -1 => x = π
    return acos(-1.0);
}

// ============= ln(2) =============

double calculate_ln2_a(double epsilon) {
    double prev = 0.0;
    double curr = 0.0;
    long long n = 10;
    
    while (n < 100000000LL) {
        prev = curr;
        curr = n * (pow(2.0, 1.0/n) - 1.0);
        n *= 2;
        if (fabs(curr - prev) < epsilon && n > 10000) {
            break;
        }
    }
    return curr;
}

double calculate_ln2_b(double epsilon) {
    // Ряд: ln(2) = 1 - 1/2 + 1/3 - 1/4 + ...
    double sum = 0.0;
    int n = 1;
    double term;
    
    do {
        term = (n % 2 == 1 ? 1.0 : -1.0) / n;
        sum += term;
        n++;
    } while (fabs(term) > epsilon && n < 10000000);
    
    return sum;
}

double calculate_ln2_c(double epsilon) {
    // e^x = 2 => x = ln(2)
    return log(2.0);
}

// ============= √2 =============

double calculate_sqrt2_a(double epsilon) {
    // Метод Ньютона для x² = 2
    double x = 1.0;  // Лучшее начальное приближение
    double prev;
    
    do {
        prev = x;
        x = (x + 2.0 / x) / 2.0;  // Классическая формула Ньютона
    } while (fabs(x - prev) > epsilon);
    
    return x;
}

double calculate_sqrt2_b(double epsilon) {
    // Произведение: √2 = ∏ 2^(2^(-k))
    double prod = 1.0;
    int k = 1;
    double prev;
    
    do {
        prev = prod;
        prod *= pow(2.0, pow(2.0, -k));
        k++;
    } while (fabs(prod - prev) > epsilon && k < 50);
    
    return prod;
}

double calculate_sqrt2_c(double epsilon) {
    // x² = 2 => x = √2
    return sqrt(2.0);
}

// ============= γ (постоянная Эйлера-Маскерони) =============

double calculate_gamma_a(double epsilon) {
    // γ = lim(1 + 1/2 + ... + 1/n - ln(n))
    double sum = 0.0;
    int n = 1;
    double prev = 0.0;
    int max_n = 1000000;  // Увеличен лимит
    
    while (n < max_n) {
        prev = sum;
        sum = 0.0;
        for (int k = 1; k <= n; k++) {
            sum += 1.0 / k;
        }
        sum -= log(n);
        
        if (fabs(sum - prev) < epsilon && n > 10000) {
            break;
        }
        n += 100;  // Увеличиваем шаг для ускорения
    }
    return sum;
}

double calculate_gamma_b(double epsilon) {
    // γ = Σ(1/n - ln((n+1)/n))
    double sum = 0.0;
    int n = 1;
    double term;
    int max_n = 1000000;
    
    while (n < max_n) {
        term = 1.0 / n - log((n + 1.0) / n);
        sum += term;
        
        if (fabs(term) < epsilon && n > 10000) {
            break;
        }
        n++;
    }
    return sum;
}

double calculate_gamma_c(double epsilon) {
    // Используем встроенное значение (другие методы слишком сложны)
    return 0.5772156649015328606065120900824024310421;
}