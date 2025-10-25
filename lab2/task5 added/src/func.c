#include "../include/func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void norm_string(char *string){
    size_t len = strlen(string);
    char * sss = malloc(len+1);
    int k = 0;
    int flag = 1;
    for(size_t i =0; string[i]!='\0' && string[i]!='\n'; i++){
        if (!(string[i] == '\t' || string[i] == ' ')){
            flag = 0;
            sss[i-k] = string[i];
        } 
        else if (string[i] == '\t' || string[i] == ' '){
            if (flag ==0){
                sss[i-k] = ' ';
                flag = 1;
            }
            else{
                k+=1;
            }
        }
    }
    if (sss[len-k-1] == ' ' || sss[len-k-1] == '\t') k++;
    sss[len-k] = '\0';
    strcpy(string, sss);
    free(sss);
}

char * obrez(char * string){
    size_t len =strlen(string);
    char *castrt = malloc(len + 1);
    char *buf = malloc(len + 1);
    int i = 79;
    if (len <= 80) {
        strcpy(castrt, string);
        i = len -1;
        while(castrt[i] ==' ') castrt[i] = '\0';
        string[0] = '\0';
        free(buf);
        return castrt;
    }
    if (string[i+1] ==' ' && string[i]!=' '){
        i++;
    }
    else{
    while (string[i] != ' ' && i != 0){
        i--;
    }
    if (i == 0){
        i = 79;
        while (string[i] != ' ' && i != len) {
            i++;
        }
    }
    }
    strncpy(castrt, string, i);
    castrt[i] = '\0';
    int k = 0;
    while (string[i]!='\0') {
       buf[k++] = string[i++];
    }
    memset(string, '\0', len); 
    buf[k] = '\0';
    if (buf[0] ==' ') k = 1;
    else k = 0;
    i = 0;
    while (buf[k]!= '\0') {
        string[i++] = buf[k++];
    }
    string[k] = '\0';
    free(buf);
    return castrt;
}

char* sdvig(char *string, int k) {
    int len = strlen(string);
    char *sstring = realloc(string, len + 2);
    if (string == NULL) return NULL;
    if (sstring == NULL) return string;
    for (int i = len; i > k; i--) {
        sstring[i + 1] = sstring[i];
    }
    sstring[k + 1] = ' ';    
    sstring[len + 1] = '\0';
    return sstring;
}
char *  add_probel(char* string){
    int i = 0;
    if (!memchr(string, ' ', strlen(string))){
        while (strlen(string)< 80) {
            string[strlen(string)] = ' ';
        }
    }
    while (strlen(string)<80) {
        if (string[i] ==' '){
            string = sdvig(string, i);
            i++;
        }
        i++;
        if (i >= 80) i=0;
    }
    return string;
}

