#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>

int  func_a(char * num);
unsigned int func_b(char* num);
int func_c(char * num, int base);
int func_d(char * num, int base);
char* read_sss(FILE *stream);
unsigned int * fibonach(int * len);
int oversscanf(const char *str, const char *format, ...);
int overfscanf(FILE *stream, const char *format, ...);
#endif