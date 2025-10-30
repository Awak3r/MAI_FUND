#include "../include/func.h"
#include <stddef.h>
#include <stdlib.h>



void *memchr(const void *str, int c, size_t n){
    unsigned char C = (unsigned char)c;
    const unsigned char * sstr =  (const unsigned char *)str;
    for (int i = 0; i<n; i++){  
        if (sstr[i]== C ){
           return (void *)(sstr+i); 
        }
    }
    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n){
    const unsigned char  * sstr1 = (const unsigned char  *) str1;
    const unsigned char  * sstr2 = (const unsigned char  *) str2;
    for (int i = 0; i< n; i++){
        if (sstr1[i] != sstr2[i]){
            return sstr1[i] - sstr2[i];
        }
    }
    return 0;

}

void *memcpy(void *dest, const void *src, size_t n){
    unsigned char *sstr1 = (unsigned char *)dest;
    const unsigned char *sstr2 = (const unsigned char *)src;
    for (int i = 0; i < n; i++){
        sstr1[i] = sstr2[i];
    }
    return dest;

}

void *memset(void *str, int c, size_t n){
    unsigned char C = (unsigned char ) c;
    unsigned char * sstr = (unsigned char *)str;
    for (int i = 0; i<n; i++){
        sstr[i] = C;
    }
    return str;
}

char *strncat(char *dest, const char *src, size_t n){
        size_t len1 = strlen(dest);
        int i;
        for (i = 0; i<n && src[i] != '\0'; i++){
            dest[len1+i] = src[i];
        }
        dest[len1 + i] = '\0';
        return  dest;
}

char *strchr(const char *str, int c){
    unsigned char C = (unsigned char)c;
    size_t len1 = strlen(str);
    for (int i = 0; i< len1+1; i++){
        if (str[i] == C){
            return (char *) str + i;
        }
    }
    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n){
    for (int i = 0; i< n; i++){
        if (str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        if (str1[i] == '\0'){
            return 0;
        }
    }
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n){
    int i;
    for (i = 0; i < n && src[i] !='\0'; i++){
        dest[i] = src[i];
    }
    while(i < n){
        dest[i] = '\0';
        ++i;
    }
    return dest;
}

size_t strcspn(const char *str1, const char *str2){
    size_t m = 0;
    for (int  i = 0; i< strlen(str1); i++){
        for (int  j = 0; j < strlen(str2); j++){
            if (str1[i] == str2[j]){
                m = i;
                return m;
            }
        }
    }
    return strlen(str1);
}

size_t strlen(const char *str){
    size_t i =0;
    while(str[i] !='\0'){
        ++i;
    }
    return i;
}

char *strpbrk(const char *str1, const char *str2){
    for (int  i = 0; i< strlen(str1); i++){
        for (int  j = 0; j < strlen(str2); j++){
            if (str1[i] == str2[j]){
                return (char *)(str1 + i);
            }
        }
    }
    return NULL;
}

char *strrchr(const char *str, int c){
     unsigned char C = (unsigned char)c;
    for (int i = strlen(str); i>=0; i--){
        if (str[i] == C){
            return (char *)(str+i);
        }
    }
    return  NULL;
}

char *strstr(const char *haystack, const char *needle){
    int k = 0;
    for (int i = 0; i<strlen(haystack); i++){
        if (haystack[i] == needle[0]){
            while (k!=strlen(needle)) {
                if (haystack[i+k] != needle[k]){
                    break;
                }
                ++k;
            }
            if (k == strlen(needle)){
                return (char *)(haystack+i);
            }
            k = 0;
        }
    }
    return NULL;
}

char *strtok(char *str, const char *delim){
    int i = 0;
    char * probel_a = str;
    char * probel_b = NULL;
    if (str == NULL){
        str = NULL;
        return NULL;
    }
    while (str[i] != '\0' && strchr(delim, str[i]) != NULL) {
        ++i;
    }
    if (i == strlen(str)){
        return NULL;
    }
    if (str[i] != '\0'){
        str[i] = '\0';
        probel_b = str + i +1;
    }
    return probel_a;
}