#include "../include/func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char * add_probel(char* string) {
    int len = strlen(string);
    if (len >= 80) {
        return string;
    }
    int space_count = 0;
    int i = 0;
    while (i < len) {
        if (string[i] == ' ') {
            space_count++;
            while (i < len && string[i] == ' ') {
                i++;
            }
        } else {
            i++;
        }
    }
    if (space_count == 0) {
        char *new_str = realloc(string, 81);
        if (!new_str) return string;
        while (strlen(new_str) < 80) {
            new_str[strlen(new_str)] = ' ';
        }
        new_str[80] = '\0';
        return new_str;
    }
    int spaces_to_add = 80 - len;
    char *new_str = malloc(81);
    if (!new_str) return string;
    int new_pos = 0;
    int added = 0;
    i = 0;
    while (i <len && new_pos< 80) {
        if (string[i] == ' ') {
            int space_group_start = i;
            while (i < len && string[i] == ' ') {
                new_str[new_pos++] = ' ';
                i++;
            }
            if (added < spaces_to_add && space_count > 0) {
                int to_add = (spaces_to_add - added + space_count - 1) / space_count;
                for (int j = 0; j< to_add && new_pos < 80 && added < spaces_to_add; j++) {
                    new_str[new_pos++] = ' ';
                    added++;
                }
                space_count--;
            }
        } else {
            new_str[new_pos++] = string[i++];
        }
    }
    new_str[new_pos] = '\0';
    free(string);
    return new_str;
}
