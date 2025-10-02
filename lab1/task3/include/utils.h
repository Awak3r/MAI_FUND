#ifndef UTILS_H
#define UTILS_H


int is_permutation_unique(float perms[][3], const int count, const float a, const float b, const float c, const float epsilon);
int is_number(const char *x);
int tupoi_epsilon(const float a, const float b, const float epsilon);
float * uravn(const float a, const float b, const float c, const float epsilon, int * length);

#endif