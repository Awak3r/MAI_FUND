#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/func.h"


int main(int argc, char ** argv)
{
    char chisl[10];
    fgets(chisl, sizeof(chisl), stdin);
    int n = atoi(chisl);
    if (n>36 || n<2 ){
        fprintf(stderr,"error: wrong base\n");
        return -1;
    }
    char string[1024];
    long number;
    long max_number = 0;
    while (strcmp(fgets(string, sizeof(chisl), stdin), "Stop\n") != 0) {\
        if(!test_in(string, n)){
            fprintf(stderr, "error: invalid number\n");
            return -1;
        }
        number = in_to_10number(string, n);
        if (labs(number) > labs(max_number)){
            max_number = number;
        }
    }
    char max_number9[256];
    char max_number18[256];
    char max_number27[256];
    char max_number36[256];
    convert_to_n(max_number, 9, max_number9);
    convert_to_n(max_number, 18, max_number18);
    convert_to_n(max_number, 27, max_number27);
    convert_to_n(max_number, 36, max_number36);
    fprintf(stdout, "%ld\n(9) %s\n(18) %s\n(27) %s\n(36) %s\n", \
        max_number, max_number9, max_number18, max_number27, max_number36);


}