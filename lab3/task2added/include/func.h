#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>


//#define VECTOR_TYPE_HARD

#ifdef VECTOR_TYPE_HARD
    #define VECTOR_TYPE char*
#else
    #define VECTOR_TYPE int
#endif


typedef struct {
    VECTOR_TYPE *data;
    size_t size;
    size_t capacity;
    int (*is_equal)(VECTOR_TYPE, VECTOR_TYPE);
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);
    void (*DeleteVoidPtr)(VECTOR_TYPE);
} Vector;

#ifdef VECTOR_TYPE_HARD
VECTOR_TYPE CopyVoidPtr_hard(VECTOR_TYPE copy);
void DeleteVoidPtr_hard(VECTOR_TYPE to_del);
int is_equal_hard(VECTOR_TYPE n1, VECTOR_TYPE n2);
#endif

VECTOR_TYPE CopyVoidPtr_simple(VECTOR_TYPE copy);
void DeleteVoidPtr_simple(VECTOR_TYPE to_del);
int is_equal_simple(VECTOR_TYPE n1, VECTOR_TYPE n2);
Vector create_vector(size_t initial_capacity, int (*is_equal_func)(VECTOR_TYPE, VECTOR_TYPE), VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE));
void erase_vector(Vector *v);
void copy_vector(Vector *dest, const Vector *src);
Vector *copy_vector_new(const Vector *src); 
int is_equal_vector(const Vector *v1, const Vector *v2);
void push_back_vector(Vector *v, VECTOR_TYPE value);
void delete_at_vector(Vector *v, size_t index);
VECTOR_TYPE get_at_vector(const Vector *v, size_t index);
void delete_vector(Vector *v);

#endif