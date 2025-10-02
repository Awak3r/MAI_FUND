#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/func.h"


int main(int argc, char **argv)
{
    if (argc!=3){
        fprintf(stderr, "error: incorect number of arguments\n");
        exit(EXIT_FAILURE);
    }
    const int x = atoi(argv[1]);
    size_t length = strlen(argv[2]);
    if (argv[2][0] != '-' && argv[2][0] != '/'){
        fprintf(stderr, "error: wrong flag's format\n");
        exit(EXIT_FAILURE);
    }
    const char flag= argv[2][1];
    if (flag != 'h' && flag != 'p' && flag != 's' && flag != 'e' && flag != 'a' && flag != 'f'){
        fprintf(stderr, "error: wrong flag\n");
        exit(EXIT_FAILURE);
    }
    int result1;
    int * result2, len;
    long long result3;
    int i = 0;
    switch (flag) {
        case 'h':
            i = 0;
            result2 = func_a(x, &len);
            if (result2 == NULL){
                fprintf(stdout, "no numbers found\n");
            }
            else{
                while(len != i){
                    fprintf(stdout, "%d ", result2[i]);
                    ++i;
                }
                fprintf(stdout, "\n");
            }
            free(result2);
        break;
        case 'p':
            result1 = func_b(x);
            if (result1 == 1){
                fprintf(stdout, "number is simple\n");
            }
            else{
                fprintf(stdout, "number is not simple\n");
            }
        break;
        case 's':
            result2 = func_c(x, &len);
            if (result2 == NULL){
                fprintf(stderr, "error: cant add memory\n");
                exit(EXIT_FAILURE);
            }
            while(i!=len){
                    fprintf(stdout, "%d ", result2[len - i - 1]);
                    ++i;
                }
                fprintf(stdout, "\n");
            free(result2);
            break;
        case 'e':
                if (x>10 || x<1){
                    fprintf(stderr, "a less than 10 required\n");
                    exit(EXIT_FAILURE);
                }
                else {
                    func_d(x);
                }
        break;
        case 'a': 
            result1 = func_e(x);
            if (result1 == -1){
                fprintf(stderr, "error: cant be counted\n");
                exit(EXIT_FAILURE);
            }
            fprintf(stdout, "%d\n", result1);
        break;
        case 'f':
            result3 = func_f(x);
            if (result3 == -1){   
                fprintf(stderr, "error: cant be counted\n");
                exit(EXIT_FAILURE);
            }
            fprintf(stdout, "%lld\n", result3);
        break;
    }
}