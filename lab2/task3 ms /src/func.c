#include "../include/func.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


char * func_a(int num){ 
    char * r1[] = {"","I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    char * r2[] = {"","X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    char * r3[] = {"","C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    char * r4[] = {"","M", "MM", "MMM", "MV'", "V'", "V'M", "V'MM", "V'MMM", "MX'"};
    char * r5[] = {"","X'", "X'X'", "X'X'X'", "X'L'", "L'", "L'X'", "L'X'X'", "L'X'X'X'", "X'C'"};
    char * r6[] = {"","C'", "C'C'", "C'C'C'", "C'D'", "D'", "D'C'", "D'C'C'", "D'C'C'C'", "C'M'"};
    char * r7[] = {"","M'", "M'M'", "M'M'M'", "M'V'", "V'", "V'M'", "V'M'M'", "V'M'M'M'", "M'X'"};
    char  * str = malloc(64* sizeof(char));
    int i = 0, cur;
    char * R;
    for(ssize_t j =7; j>=1; j--){
        cur = (num%(int)pow(10,j))/(int)pow(10, j-1);
        switch (j) {
            case 1:
            R = r1[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
            case 2:
            R = r2[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
            case 3:
            R = r3[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
            case 4:
            R = r4[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
            case 5:
            R = r5[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
            case 6:
            R = r6[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
            case 7:
            R = r7[cur];
            for(size_t k = 0; k<strlen(R); k++){
                str[i++] = R[k];
            }
            break;
        
        }
    }
    str[i] = '\0';
    return str;
}

char * func_b(unsigned int num){
    char * s1 = malloc(sizeof(char)*100);
    char * s2 = malloc(sizeof(char)*100);
    if (num == 1){
        s2[0] = '1';
        s2[1] = '1';
        free(s1);
        return s2;
    }
    int * len = malloc(sizeof(int));
    unsigned int * fib = fibonach(len);
    int k = 0, i, flag = 1;
    for (i = *len - 1; i>=0; i--){
        if (num >= fib[i]){
            s1[k++] = '1';
            num-=fib[i];
            s1[k++] = '0';
            i--;
            flag = 0;
        }
        else if (flag == 0){
            s1[k++] = '0';

        }
    }
    s1[k] = '\0'; 
    for(i = 0; i<k; i++){
        s2[i] = s1[k-i-1];
    }
    s2[k++] = '1';
    s2[k] = '\0';
    free(s1);
    free(len);
    return s2;
}

char * func_c(int num, int base){
    if (base<2 || base > 36) base = 10;
    char * digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *res1 = malloc(sizeof(char) * 100);
    char *res2 = malloc(sizeof(char) * 100);
    if (num == 0) return "0";
    int flag = 0;
    if (num < 0){
        flag = 1;
        num*=-1;
    }
    int i = 0, k = 0;
    while (num>0) {
        res1[i++] = digits[num%base];
        num/=base;
    }
    if (flag == 1) res1[i++] = '-';
    i--;
    while (i>=0) {
        res2[k++] = res1[i--];
    }
    res2[k++] = '\0';
    free(res1);
    return res2;


}

char * func_d(int num, int base){
    char * res1 = func_c(num, base);
    for(int i = 0; res1[i]!='\0'; i++){
        res1[i] = toupper(res1[i]);
    }
    return res1;

}

int func_e(char * num, int base){
    int res = 0;
    int len = strlen(num);
    char * digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *index;
    int ind;
    if (base < 2 || base > 36) base = 10;
    int i;
    for(i = 0; i<len; i++){
        if (num[i] >='A' && num[i] <='Z') return -1;
        index = memchr(digits, num[i], strlen(digits));
        if (index == NULL)return -1;
        ind = index - digits;
        if (ind>=base) return -1;
        res+=ind* pow(base, len -i -1);
    }
    return res;
}

int func_f(char * num, int base){
    char * num1 = malloc(sizeof(char)*(strlen(num)+10));
    for(int i = 0; i<strlen(num); i++){
        if (num[i] >='a' && num[i] <='z') return -1;
        num1[i] = tolower(num[i]);
    }
    int res = func_e(num1, base);
    return res;
}

char * func_g(int num){
    unsigned char *bytes = (unsigned char*)&num;
    char * nn = malloc(sizeof(char)*(4*8+4));
    int k = 0;
    for(int i =0; i<4; i++){
        for (int j = 7; j >= 0; j--) {
            nn[k++] = ((bytes[i] >> j) & 1) + '0';
        }
        if (i < 3) nn[k++] = ' ';
    }
    nn[k] = '\0';
    return nn;
}

char * func_h(unsigned int num){
    unsigned char *bytes = (unsigned char*)&num;
    char * nn = malloc(sizeof(char)*(4*8+4));
    int k = 0;
    for(int i =0; i<4; i++){
        for (int j = 7; j >= 0; j--) {
            nn[k++] = ((bytes[i] >> j) & 1) + '0';
        }
        if (i < 3) nn[k++] = ' ';
    }
    nn[k] = '\0';
    return nn;
}

char * func_i(double num){
    unsigned char *bytes = (unsigned char*)&num;
    char * nn = malloc(sizeof(char)*(8*8 + 8)); 
    int k = 0;
    for(int i = 0; i < 8; i++){
        for (int j = 7; j >= 0; j--) {
            nn[k++] = ((bytes[i] >> j) & 1) + '0';
        }
        if (i < 7) nn[k++] = ' ';
    }
    nn[k] = '\0';
    return nn;
}

char * func_j(float num){
    unsigned char *bytes = (unsigned char*)&num;
    char * nn = malloc(sizeof(char)*(4*8+4));
    int k = 0;
    for(int i =0; i<4; i++){
        for (int j = 7; j >= 0; j--) {
            nn[k++] = ((bytes[i] >> j) & 1) + '0';
        }
        if (i < 3) nn[k++] = ' ';
    }
    nn[k] = '\0';
    return nn;
}

unsigned int * fibonach(int * len){
    unsigned int f1 = 1, f2 = 1, k;
    unsigned int * sss = malloc(sizeof( unsigned int)* 100);
    if (!sss) return NULL;
    sss[0] = 1;
    size_t i;
    for(i = 1; i<100; i++){
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


#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buf[1024];
    int pos = 0;
    size_t flen = strlen(format);

    for (size_t i = 0; i < flen; i++) {
        if (format[i] == '%') {
            if (strncmp(&format[i], "%Ro", 3) == 0) {
                int V = va_arg(args, int);
                char * v = func_a(V);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%Zr", 3) == 0) {
                int V = va_arg(args, unsigned int);
                char * v = func_b(V);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%Cv", 3) == 0) {
                int V1 = va_arg(args, int);
                int V2 = va_arg(args, int);
                char * v = func_c(V1,V2);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%CV", 3) == 0) {
                int V1 = va_arg(args, int);
                int V2 = va_arg(args, int);
                char * v = func_d(V1,V2);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%to", 3) == 0) {
                char * V1 = va_arg(args, char *);
                int V2 = va_arg(args, int);
                int v = func_e(V1,V2);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%d", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%TO", 3) == 0) {
                char * V1 = va_arg(args, char *);
                int V2 = va_arg(args, int);
                int v = func_f(V1,V2);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%d", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%mi", 3) == 0) {
                int V = va_arg(args, int);
                char * v = func_g(V);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%mu", 3) == 0) {
                unsigned int V = va_arg(args, unsigned int);
                char * v = func_h(V);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%md", 3) == 0) {
                double V = va_arg(args, double);
                char * v = func_i(V);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            if (strncmp(&format[i], "%mf", 3) == 0) {
                float V = va_arg(args, double);
                char * v = func_j(V);
                pos+=snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                i++;
                continue;
            }
            switch(format[i+1]) {
                case 'd': case 'i': {
                    int v = va_arg(args, int);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%d", v);
                    i++;
                } break;
                case 'u': {
                    unsigned int v = va_arg(args, unsigned int);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%u", v);
                    i++;
                } break;
                case 'f': {
                    double v = va_arg(args, double);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%f", v);
                    i++;
                } break;
                case 'x': case 'X': {
                    int v = va_arg(args, int);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, (format[i+1] == 'x' ? "%x" : "%X"), v);
                    i++;
                } break;
                case 'o': {
                    int v = va_arg(args, int);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%o", v);
                    i++;
                } break;
                case 's': {
                    const char *v = va_arg(args, const char*);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%s", v);
                    i++;
                } break;
                case 'c': {
                    int v = va_arg(args, int);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%c", v);
                    i++;
                } break;
                case 'p': {
                    void *v = va_arg(args, void*);
                    pos += snprintf(buf + pos, sizeof(buf) - pos, "%p", v);
                    i++;
                } break;
                case '%': {
                    buf[pos++] = '%';
                    i++;
                } break;
                default:
                    buf[pos++] = '%';
            }
        } else {
            buf[pos++] = format[i];
        }
    }
    buf[pos] = '\0';
    strcpy(str, buf);

    va_end(args);
    return pos;
}

int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buf[1024];
    int written = oversprintf(buf, format, args); 
    fputs(buf, stream);

    va_end(args);
    return written;
}




