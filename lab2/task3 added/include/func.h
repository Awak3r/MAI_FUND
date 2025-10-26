#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>

char * func_a(int num);
unsigned int * fibonach(int * len);
char * func_b(unsigned int num);
char * func_c(int num, int base);
char * func_d(int num, int base);
int func_e(char * num, int base);
int func_f(char * num, int base);
char * func_g(int num);
char * func_h(unsigned int num);
char * func_i(double num);
char * func_j(float num);
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);
#endif