#include "../include/func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef VECTOR_TYPE_HARD
VECTOR_TYPE CopyVoidPtr_hard(VECTOR_TYPE copy){
    if (!copy) return NULL;
    size_t len = 0;
    while (copy[len]!='\0') {
        len++;
    }
    VECTOR_TYPE res = (VECTOR_TYPE)malloc(len + 1);
    if (!res) {
        fprintf(stderr, "error: can`t allocate memory\n");
        exit(EXIT_FAILURE); 
    }
    for(size_t i = 0; i < len; i++){
        res[i] = copy[i];
    }
    res[len] = '\0';
    return res;
}

void DeleteVoidPtr_hard(VECTOR_TYPE to_del){
    if (to_del){
        free(to_del);
    }
}



int is_equal_hard(VECTOR_TYPE n1, VECTOR_TYPE n2){
    if (!n1 || !n2) return 0;
    size_t len1 = 0, len2 = 0;
    while (n1[len1] != '\0') len1++;
    while (n2[len2] != '\0') len2++;
    if (len1 != len2) return 0;
    for (size_t i = 0; i < len1; i++){
        if (n1[i] != n2[i]) return 0;
    }
    return 1;
}
#endif

VECTOR_TYPE CopyVoidPtr_simple(VECTOR_TYPE copy){
    return copy;
}

void DeleteVoidPtr_simple(VECTOR_TYPE to_del){
    (void)to_del;
}

int is_equal_simple(VECTOR_TYPE n1, VECTOR_TYPE n2){
    if (n1 != n2) return 0;
    return 1;
}


Vector create_vector(size_t initial_capacity, int (*is_equal_func)(VECTOR_TYPE, VECTOR_TYPE), VECTOR_TYPE
(*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)){
    Vector res;
    res.size = 0;
    res.capacity = initial_capacity;
    res.is_equal = is_equal_func;
    res.CopyVoidPtr = CopyFunc;
    res.DeleteVoidPtr = DeleteFunc;
    if (initial_capacity > 0){
        res.data = (VECTOR_TYPE *)malloc(sizeof(VECTOR_TYPE)* initial_capacity);
        if (!res.data){
            fprintf(stderr, "error: can`t allocate memory\n");
            exit(EXIT_FAILURE); 
        }
    } else {
        res.data = NULL;
    }
    return res;

}

void erase_vector(Vector *v){
    if (!v) return;
    for(size_t i = 0; i< v->size; i++){
        v->DeleteVoidPtr(v->data[i]);
    }
    v->size = 0;
    v->capacity = 0;
    free(v->data);
    v->data = NULL;
}

void copy_vector(Vector *dest, const Vector *src){
    if (!dest || !src) {
        fprintf(stderr, "error: NULL pointer\n");
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < dest->size; i++){
        dest->DeleteVoidPtr(dest->data[i]);
    }
    dest->is_equal = src->is_equal;
    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;
    if (dest->capacity != src->capacity){
        VECTOR_TYPE * smp = (VECTOR_TYPE *)realloc(dest->data, sizeof(VECTOR_TYPE) * src->capacity);
        if (!smp){
            fprintf(stderr, "error: can`t allocate memory\n");
            exit(EXIT_FAILURE); 
        }
        dest->data = smp;
        dest->capacity = src->capacity;
    }
    for(size_t i = 0; i<src->size; i++){
        dest->data[i] = src->CopyVoidPtr(src->data[i]);
    }
    dest->size = src->size;
}

Vector *copy_vector_new(const Vector *src){
    if (!src) return NULL;
    Vector *new = (Vector*)malloc(sizeof(Vector));
    if (!new) return NULL;
    *new = create_vector(src->capacity, src->is_equal, src->CopyVoidPtr, src->DeleteVoidPtr);
    for (size_t i = 0; i < src->size; i++){
        new->data[i] = src->CopyVoidPtr(src->data[i]); 
    }
    new->size = src->size;
    return new;
}

void push_back_vector(Vector *v, VECTOR_TYPE value){
    if (!v) {
        fprintf(stderr, "error: NULL pointer\n");
        exit(EXIT_FAILURE); 
    }
    if (v->size< v->capacity) {
        v->data[v->size++] =v->CopyVoidPtr(value);
    } else {
        if (v->capacity!=0) v->capacity*=2;
        else v->capacity++;
        VECTOR_TYPE * smp = (VECTOR_TYPE *)realloc(v->data, sizeof(VECTOR_TYPE)*v->capacity);
        if (!smp){
            fprintf(stderr, "error: can`t allocate memory\n");
            exit(EXIT_FAILURE); 
        }
        v->data = smp;
        v->data[v->size++] = v->CopyVoidPtr(value);
    }
}

void delete_at_vector(Vector *v, size_t index){
    if (!v) {
        fprintf(stderr, "error: NULL pointer\n");
        exit(EXIT_FAILURE); 
    }
    if (index >= v->size){
        fprintf(stderr, "error: invalid index\n");
        exit(EXIT_FAILURE); 
    }
    v->DeleteVoidPtr(v->data[index]);
    for (size_t i = index; i<v->size - 1; i++){
        v->data[i] = v->data[i+1];
    }
    v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index){
    if (!v) {
        fprintf(stderr, "error: NULL pointer\n");
        exit(EXIT_FAILURE); 
    }
    if (index >= v->size){
        fprintf(stderr, "error: invalid index\n");
        exit(EXIT_FAILURE); 
    }
    VECTOR_TYPE res = v->data[index];
    return res;
}

void delete_vector(Vector *v){
    if (!v) return;
    erase_vector(v);
    free(v);
}

int is_equal_vector(const Vector *v1, const Vector *v2){
    if (!v1 || !v2) return 0;
    if (v1->size != v2->size) return 0;  
    for (size_t i = 0; i < v1->size; i++){
        if (v1->is_equal(v1->data[i], v2->data[i]) == 0) return 0;
    }
    return 1;
}
