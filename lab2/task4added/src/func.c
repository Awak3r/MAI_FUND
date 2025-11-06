#include "../include/func.h"
#include <linux/limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* read_sss(FILE *stream){
    int cap = 128, len = 0, c;
    char *buf = malloc(cap);
    if (!buf) return NULL;
    while ((c = fgetc(stream)) != EOF && isspace(c));
    if (c == EOF) {
        free(buf);
        return NULL;
    }
    buf[len++] = c;
    while ((c = fgetc(stream)) != EOF && !isspace(c)){
        if (len >= cap - 1){
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp){ 
                free(buf); 
                return NULL; 
            }
            buf = tmp;
        }
        buf[len++] = c;
    }
    if (c != EOF) ungetc(c, stream);
    buf[len] = '\0';
    return buf;
}

unsigned int * fibonach(int * len){
    unsigned int f1 = 1, f2 = 1, k;
    unsigned int * sss = (unsigned int* ) malloc(sizeof(unsigned int)* 100);
    if (!sss) return NULL;
    sss[0] = 1;
    sss[1] = 1;
    size_t i;
    for(i = 2; i<100; i++){
        if ((f1+f2) < f1 || (f1+f2) < f2){
            break;
        }
        sss[i] = (f1+f2);
        k = f1;
        f1 = f2;
        f2 = k+f2;
    }
    sss[i] = 0;
    *len = i;
    return sss;
}




int  func_a(char * num){ 
    //IVXLCDM
    if (!num || !*num) return -1;
    int res = 0, i = 0;
    int len = strlen(num);
    if (num[0] == '-') return -1;;
    while(i != len){
        switch (num[i]){
        case 'I':{
            if (num[i+1] && num[i+1] =='X'){
                res+=9;
                i+=2;
            } else if (num[i+1] && num[i+1] =='V'){
                res+=4;
                i+=2;
            } else{
                res+=1;
                i++;
            }
        } break;
        case 'V':{
            res+=5;
            i++;
        } break;
        case 'X':{
            if (num[i+1] && num[i+1] =='C'){
                res+=90;
                i+=2;
            } else if (num[i+1] && num[i+1] =='L'){
                res+=40;
                i+=2;
            } else{
                res+=10;
                i++;
            }
        } break;
        case 'L':{
            res+=50;
            i++;
        } break;
        case 'C':{
            if (num[i+1] && num[i+1] =='M'){
                res+=900;
                i+=2;
            } else if (num[i+1] && num[i+1] == 'D'){
                res+=400;
                i+=2;
            } else{
                res+=100;
                i++;
            }
        } break;
        case 'D':{
            res+=500;
            i++;
        } break;
        case 'M':{
            res+=1000;
            i++;
        } break;
        default: return -1;
        }
    }
    if (res>4000){
        return -1;
    }
    return res;
}

unsigned int func_b(char* num){
    if (!num || strlen(num)< 2) return 0;
    int len = strlen(num);
    for(int i = 0; i<len; i++){
        if (num[i] != '1' && num[i] !='0') return 0;
    }
    unsigned int res = 0;
    int len_fib; 
    int i = 0, k = 0;
    unsigned int * fib = fibonach(&len_fib);
    if (!fib) return 0;
    while(i<len_fib && num[k+1] !='\0'){
        if (num[k] == '1'){
            res+=fib[i];
            i++;
        }
        i++;
        k++;
    }
    free(fib);
    return res;
}

int func_c(char * num, int base){
    if (!num || !*num) return -1;
    long long res = 0;
    int len = strlen(num);
    long long test;
    char * digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *index;
    int ind;
    if (base < 2 || base > 36) base = 10;
    int i;
    for(i = 0; i<len; i++){
        index = memchr(digits, num[i], strlen(digits));
        if (index == NULL)return -1;
        ind = index - digits;
        if (ind>=base) return -1;
        test = ind* pow(base, len -i -1);
        if ((res + test)>INT_MAX) return -1;
        res+=test;
    }
    return (int)res;
}

int func_d(char * num, int base){
    if (!num || !*num) return -1;
    int len = strlen(num);
    char * num1 = malloc(sizeof(char)*(strlen(num)+10));
    if (!num1) return -1;
    for(int i = 0; i<len; i++){
        if (num[i] >= 'A' && num[i] <= 'Z'){
            num1[i] = tolower(num[i]);
        } else if (num[i] >= '0' && num[i] <= '9'){
            num1[i] = num[i];
        } else {
            free(num1);
            return -1;
    }
    }
    num1[len] = '\0';
    int res = func_c(num1, base);
    free(num1);
    return res;
}

int oversscanf(const char *str, const char *format, ...){
    va_list args;
    va_start(args, format);
    int pos = 0, count = 0;
    size_t flen = strlen(format);
    
    for (size_t i = 0; i < flen; i++){
        if (format[i] != '%'){
            if (isspace(format[i])){
                while (str[pos] && isspace(str[pos])) pos++;
            } else {
                if (str[pos] != format[i]){
                    va_end(args);
                    return count;
                }
                pos++;
            }
            continue;
        }
        if (format[i] == '%'){
            if (format[i+1] == '%'){
                if (str[pos] != '%'){
                    va_end(args);
                    return count;
                }
                pos++;
                i++;
                continue;
            }
            if (strncmp(&format[i], "%Ro", 3) ==0){
                int * res = va_arg(args, int*);
                char * v = malloc(sizeof(char) * (strlen(str) + 1));
                if (!v){
                    va_end(args);
                    return count;
                }
                if (sscanf(&str[pos], "%s", v) == 1){
                    pos += strlen(v);
                    int result = func_a(v);
                    free(v);
                    if (result == -1){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                } else {
                    free(v);
                }
                i += 2;
                continue;
            }
            if (strncmp(&format[i], "%Zr", 3) == 0){
                unsigned int * res = va_arg(args, unsigned int *);
                char * v = malloc(sizeof(char) * (strlen(str) + 1));
                if (!v){
                    va_end(args);
                    return count;
                }
                if (sscanf(&str[pos], "%s", v) == 1){
                    pos += strlen(v);
                    unsigned int result = func_b(v);
                    free(v);
                    if (result == 0){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                } else {
                    free(v);
                }
                i += 2;
                continue;
            }
            if (strncmp(&format[i], "%Cv", 3) == 0){
                int * res = va_arg(args, int *);
                int base = va_arg(args, int);
                char * v = malloc(sizeof(char) * (strlen(str) + 1));
                if (!v){
                    va_end(args);
                    return count;
                }
                if (sscanf(&str[pos], "%s", v) == 1){
                    pos += strlen(v);
                    int result = func_c(v, base);
                    free(v);
                    if (result == -1){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                } else {
                    free(v);
                }
                i += 2;
                continue;
            }
            
            if (strncmp(&format[i], "%CV", 3) == 0){
                int * res = va_arg(args, int *);
                int base = va_arg(args, int);
                char * v = malloc(sizeof(char) * (strlen(str) + 1));
                if (!v){
                    va_end(args);
                    return count;
                }
                if (sscanf(&str[pos], "%s", v) == 1){
                    pos += strlen(v);
                    int result = func_d(v, base);
                    free(v);
                    if (result == -1){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                } else {
                    free(v);
                }
                i += 2;
                continue;
            }
            
            switch(format[i+1]){
                case 'd': case 'i':{
                    int * v = va_arg(args, int*);
                    int chars_read;
                    if (sscanf(&str[pos], "%d%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 'u':{
                    unsigned int * v = va_arg(args, unsigned int*);
                    int chars_read;
                    if (sscanf(&str[pos], "%u%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 'f': case 'e': case 'g':{
                    double * v = va_arg(args, double*);
                    int chars_read;
                    if (sscanf(&str[pos], "%lf%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 'x':{
                    int * v = va_arg(args, int*);
                    int chars_read;
                    if (sscanf(&str[pos], "%x%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 'X':{
                    int * v = va_arg(args, int*);
                    int chars_read;
                    if (sscanf(&str[pos], "%X%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 'o':{
                    int * v = va_arg(args, int*);
                    int chars_read;
                    if (sscanf(&str[pos], "%o%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 's':{
                    char *v = va_arg(args, char*);
                    int chars_read;
                    if (sscanf(&str[pos], "%s%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;
                        count++;
                    }
                } break;
                case 'c':{
                    char * v = va_arg(args, char*);
                    int chars_read;
                    if (sscanf(&str[pos], "%c%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;                   
                        count++;
                    }
                } break;
                case 'p':{
                    void **v = va_arg(args, void**);
                    int chars_read;
                    if (sscanf(&str[pos], "%p%n", v, &chars_read) == 1){
                        pos += chars_read;
                        i++;                    
                        count++;
                    }
                } break;
                case 'n':{
                    int *v = va_arg(args, int*);
                    *v = pos;
                    i++;
                } break;
                default:
                    i++;
            }
        }
    }
    va_end(args);
    return count;
}


int overfscanf(FILE *stream, const char *format, ...){
    va_list args;
    va_start(args, format);
    int count = 0;
    int total_read = 0;
    size_t flen = strlen(format);
    
    for (size_t i = 0; i < flen; i++){
        if (format[i] != '%'){
            if (isspace(format[i])){
                int c;
                while ((c = fgetc(stream)) != EOF && isspace(c)){
                    total_read++;
                }
                if (c != EOF) ungetc(c, stream);
            } else {
                int c = fgetc(stream);
                if (c == EOF || c != format[i]){
                    if (c != EOF) ungetc(c, stream);
                    va_end(args);
                    return count;
                }
                total_read++;
            }
            continue;
        }
        
        if (format[i] == '%'){
            if (format[i+1] == '%'){
                int c = fgetc(stream);
                if (c != '%'){
                    if (c != EOF) ungetc(c, stream);
                    va_end(args);
                    return count;
                }
                total_read++;
                i++;
                continue;
            }
            if (strncmp(&format[i], "%Ro", 3) == 0){
                int * res = va_arg(args, int*);
                char * v = read_sss(stream);
                if (v){
                    total_read += strlen(v);
                    int result = func_a(v);
                    free(v);
                    if (result == -1){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                }
                i += 2;
                continue;
            }
            if (strncmp(&format[i], "%Zr", 3) == 0){
                unsigned int * res = va_arg(args, unsigned int *);
                char * v = read_sss(stream);
                if (v){
                    total_read += strlen(v);
                    unsigned int result = func_b(v);
                    free(v);
                    if (result == 0){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                }
                i += 2;
                continue;
            }
            if (strncmp(&format[i], "%Cv", 3) == 0){
                int * res = va_arg(args, int *);
                int base = va_arg(args, int);
                char * v = read_sss(stream);
                if (v){
                    total_read += strlen(v);
                    int result = func_c(v, base);
                    free(v);
                    if (result == -1){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                }
                i += 2;
                continue;
            }
            if (strncmp(&format[i], "%CV", 3) == 0){
                int * res = va_arg(args, int *);
                int base = va_arg(args, int);
                char * v = read_sss(stream);
                if (v){
                    total_read += strlen(v);
                    int result = func_d(v, base);
                    free(v);
                    if (result == -1){
                        va_end(args);
                        return -1;
                    }
                    *res = result;
                    count++;
                }
                i += 2;
                continue;
            }
            switch(format[i+1]){
                case 'd': case 'i':{
                    int * v = va_arg(args, int*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%d", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 'u':{
                    unsigned int * v = va_arg(args, unsigned int*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%u", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 'f': case 'e': case 'g':{
                    double * v = va_arg(args, double*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%lf", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 'x':{
                    int * v = va_arg(args, int*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%x", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 'X':{
                    int * v = va_arg(args, int*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%X", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 'o':{
                    int * v = va_arg(args, int*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%o", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 's':{
                    char *v = va_arg(args, char*);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%s", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;
                        count++;
                    }
                } break;
                case 'c':{
                    char * v = va_arg(args, char*);
                    if (fscanf(stream, "%c", v) == 1){
                        total_read++;
                        i++;                   
                        count++;
                    }
                } break;
                case 'p':{
                    void **v = va_arg(args, void**);
                    long pos_before = ftell(stream);
                    if (fscanf(stream, "%p", v) == 1){
                        long pos_after = ftell(stream);
                        if (pos_before != -1L && pos_after != -1L){
                            total_read += (int)(pos_after - pos_before);
                        }
                        i++;                    
                        count++;
                    }
                } break;
                case 'n':{
                    int *v = va_arg(args, int*);
                    *v = total_read;
                    i++;
                } break;
                default:
                    i++;
            }
        }
    }
    
    va_end(args);
    return count;
}

