#include <unistd.h>
#include <stdlib.h>
#include "../include/utils.h"
#include <math.h>


int is_number(const char *x) {
    if (x == NULL || *x == '\0') {
        return 0;
    }
    char *end;
    strtod(x, &end);
    return *end == '\0';
}

int tupoi_epsilon(const float a, const float b, const float epsilon){
return fabs(a - b) < epsilon;
}


int is_permutation_unique(float perms[][3], const int count, const float a, const float b, const float c, const float epsilon){
    int i;
    for (i = 0; i < count; i++){
        if (tupoi_epsilon(perms[i][0], a, epsilon) && tupoi_epsilon(perms[i][1], b, epsilon) && tupoi_epsilon(perms[i][2], c, epsilon)){
            return 0;
        }
    }
    return 1;
}
float * uravn(const float a, const float b, const float c, const float epsilon, int * length){
    float * res = malloc(sizeof(float) * 3);
    int i = 0;
    if (tupoi_epsilon(a, 0.0, epsilon)){
        if (tupoi_epsilon(b, 0.0, epsilon)){
            if (tupoi_epsilon(c, 0.0, epsilon)){
                *length = -1;
                return res;
            }
            else {
                *length = i;
                return res;
            }
        }
        else {
            const float x = -c / b;
            res[i++] = x;
            *length = i;
            return res;
            }

    }
    const float discriminant = b * b - 4 * a * c;
    if (discriminant < -epsilon){
        *length = i;
        return res;
    }
    else if (tupoi_epsilon(discriminant, 0.0, epsilon)){
        const float x = -b / (2 * a);
        res[i++] = x;
        *length = i;
        return res;
    }
    else {
        const float sqrt_d = sqrt(discriminant);
        const float x1 = (-b + sqrt_d) / (2 * a);
        const float x2 = (-b - sqrt_d) / (2 * a);
        res[i++] = x1;
        res[i++] = x2; 
        *length = i;
        return res;
    }
}


