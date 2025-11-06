#include "include/func.h"
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <sys/ucontext.h>

int main(){
    int n = test(1.0/3, 10);
    fprintf(stdout, "%d\n", n);
}