#include "../include/func.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int check_brackets(const char *str){
    size_t len = strlen(str);
    char * kucha = malloc((len+1) * sizeof(char));
    int k = -1;
    char s;
    for (size_t i = 0; i<len; i++){
        if (str[i] =='(' || str[i] == '[' || str[i] == '{' || str[i] == '<'){
            kucha[++k] = str[i];
        }
        if (str[i] ==')' || str[i] == ']' || str[i] == '}' || str[i] == '>'){
            if (k!=-1){
                s = kucha[k--];
                switch (s) {
                    case '(': {
                        if (str[i] != ')') {
                            free(kucha); 
                            return 0;
                        }
                    }break;
                    case '[': {
                        if (str[i] != ']') {
                            free(kucha); 
                            return 0;
                        }
                    }break;
                    case '{': {
                        if (str[i] != '}') {
                            free(kucha); 
                            return 0;
                        }
                    }break;
                    case '<': {
                        if (str[i] != '>') {
                            free(kucha); 
                            return 0;
                        }
                    }break;
                }
            } else {
                free(kucha); 
                return 0;
            }
        }
    }
    free(kucha);
    if (k == -1) return 1;
    return 0;
}