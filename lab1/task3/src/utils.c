#include <stdlib.h>
#include <math.h>
#include "../include/utils.h"

int is_number(const char *x){
    if (x == NULL || *x == '\0'){
        return 0;
    }
    char *end;
    strtod(x, &end);
    return *end == '\0';
}

int tupoi_epsilon(const float a, const float b, const float epsilon){
    return fabsf(a - b) < epsilon;
}

int is_permutation_unique(float perms[][3], const int count, const float a, const float b, const float c, const float epsilon){
    for (int i = 0; i < count; i++){
        if (tupoi_epsilon(perms[i][0], a, epsilon) && 
            tupoi_epsilon(perms[i][1], b, epsilon) && 
            tupoi_epsilon(perms[i][2], c, epsilon)){
            return 0;
        }
    }
    return 1;
}

float* uravn(const float a, const float b, const float c, const float epsilon, int* length){
    float* res = malloc(sizeof(float) * 2);
    *length = 0;
    
    if (tupoi_epsilon(a, 0.0f, epsilon)){
        if (tupoi_epsilon(b, 0.0f, epsilon)){
            if (tupoi_epsilon(c, 0.0f, epsilon)){
                *length = -1; 
            } else {
                *length = 0; 
            }
        } else {
            res[0] = -c / b;
            *length = 1;
        }
        return res;
    }
    

    const float discriminant = b * b - 4.0f * a * c;
    
    if (discriminant < -epsilon){
        *length = 0; 
    } else if (tupoi_epsilon(discriminant, 0.0f, epsilon)){
        res[0] = -b / (2.0f * a);
        *length = 1;
    } else {
        const float sqrt_d = sqrtf(discriminant);
        res[0] = (-b + sqrt_d) / (2.0f * a);
        res[1] = (-b - sqrt_d) / (2.0f * a);
        *length = 2;
    }
    
    return res;
}