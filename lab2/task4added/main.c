#include "include/func.h"
#include <stdio.h>
int main(int argc, char ** argv)
{
    double result = 0.0;
    int count = oversscanf("3.14", "%lf", &result);
    fprintf(stdout, "%lf", result);
}
