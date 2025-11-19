#ifndef POST_OFFICE_FUNC_H
#define POST_OFFICE_FUNC_H
#include "../include/mail_func.h"
#include <stddef.h>
#include <stdio.h>


typedef struct{
    unsigned int ID;
    size_t max_capacity;
    mail_heap * mail_heap_array;
    size_t connection_count;
    int * connected_offices;
} post_office;

typedef struct {
    post_office * post_office_array;
    size_t size;
    size_t capacity;
} office_heap;

office_heap* create_office_heap(size_t initial_capacity);
void delete_office_heap(office_heap *heap);
int is_empty_office_heap(office_heap *heap);
int peek_office_heap(office_heap *heap, post_office *result);
int push_office_heap(office_heap *heap, post_office value);
int pop_office_heap(office_heap *heap, post_office *result);
int build_office_heap(office_heap *heap, post_office *array, size_t array_size);
int is_equal_office_heap(office_heap *heap1, office_heap *heap2);
size_t size_office_heap(office_heap *heap);

post_office * create_post_office(unsigned int ID, size_t max_capacity, mail_heap * mail_heap_array, 
    size_t connection_count, int * connected_offices);
void delete_post_office(post_office * office);
int is_equal_post_office(post_office * p1,post_office * p2);
int add_mail(post_office * p, mail * mail);
mail * get_mail(post_office * p);
void print_menu();
#endif