#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/func.h"
#include <limits.h>


int read_number() {
    char buffer[32];
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytes_read<=0){
        return -1;
    }
    return atoi(buffer);
}

int * simple_numbers(int * simple_len)
{
    int max_n = 1000000, n=0, j;
    char* numbers = (char*)malloc(max_n * sizeof(char));
    int*simple = (int*)malloc(sizeof(int)*max_n);
    memset(numbers, 1, max_n);
    numbers[0] = 0, numbers[1] = 0;
    for (int i = 2; i<max_n; i++){
        if (numbers[i]){
            simple[n++]=i;
            j = i * i;
            while(j<max_n){
                numbers[j] = 0;
                j+=i;
            }
        }
    } 
    for (int i = 2; i < max_n; i++) {
        if (numbers[i] && i*i >= max_n){  
            simple[n++] = i;
        }
    }
    free(numbers);
    *simple_len = n;
    return simple;
}

int task2(int * simple, int n) {
    return simple[n-1];
}