#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/func.h"



int read_number() {
    char buffer[sizeof(int)];
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytes_read<=0){
        return -1;
    }
    return atoi(buffer);
}
int del_count(int num)
{   if (num<2) return 0;
    if (num==2) return 1;
    if (num%2==0) return 0;
    for (int i=3; i*i<=num; i+=2){
        if (num%i==0){
            return 0;
        }
    }
    return 1;
}

int * simple_numbers(int * simple_len)
{
    int max_n = 10000000, n=0;
    int * numbers = malloc(sizeof(int)* max_n);
    if (!numbers) return NULL;
    for (int i = 2; i<max_n; i++){
        if (del_count(i)){
           numbers[n]=i;
           ++n;
        }
    }
    int *numbers2 = realloc(numbers, sizeof(int) * n);
    if (!numbers2) {
        free(numbers);
        return NULL;
    }
    *simple_len = n;
    return numbers2;
}

int task2(int * simple, int n) {
    return simple[n-1];
}