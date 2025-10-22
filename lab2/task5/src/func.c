#include "../include/func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void norm_string(char string[]){
    char sss[1024];
    int k = 0;
    int flag = 1;
    for(ssize_t i =0; string[i]!='\0' && string[i]!='\n'; i++){
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
    if (sss[strlen(string)-k-1] == ' ' || sss[strlen(string)-k-1] == '\t') k++;
    sss[strlen(string)-k] = '\0';
    strcpy(string, sss);
}

char * obrez(char * string){
    char *castrt = malloc(sizeof(char)*1024);
    char *buf = malloc(sizeof(char)*1024);
    int i = 79;
    if (strlen(string)<=80) {
        strcpy(castrt, string);
        string[0] = '\0';
        return castrt;
    }
    if (string[i+1] ==' ' && string[i]!=' '){
        strncpy(castrt, string,80);
        i+=1;
    }
    else{
    while (string[i] != ' ' && i != 0){
        i-=1;
    }
    if (i == 0){
        i = 79;
        while (string[i] != ' ' && i != (strlen(string))) {
            i+=1;
        }
        strncpy(castrt, string,i);
    }
    else{
        strncpy(castrt, string, i);
    }
    }
    castrt[i] = '\0';
    int k = 0;
    while (string[i]!='\0') {
       buf[k++] = string[i];
       i++;
    }
    memset(string, '\0', strlen(string));
    buf[k] = '\0';
    k=0;
    int ff =0, ffk = 0;
    while (buf[k]!='\0') {
        if (ff == 0 && buf[k] ==' ') {
            ffk+=1;
        }
        else if (ff == 0 && buf[k] !=' ') {
            ff = 1;
            string[k-ffk] = buf[k];
        }
        else{
        string[k-ffk] = buf[k];
        }
        k++; 
    }
    string[k] = '\0';
    free(buf);
    return castrt;
}
char* sdvig(char *string, int k) {
    int len = strlen(string);
    char *sstring = realloc(string, len + 2);
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
    if (!memchr(string, ' ', sizeof(string))){
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

