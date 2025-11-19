#ifndef MAIL_FUNC_H
#define MAIL_FUNC_H
#include <stddef.h>
#include <stdio.h>

# define minimal_capacity 16
# define minimal_length 512

typedef struct {
    unsigned int mail_id;             
    char  * type;           
    int priority;             
    unsigned int sender_office_id;     
    unsigned int recipient_office_id;  
    char * status;          
    char * tech_data;     
} mail;

typedef struct {
    mail *mail_array;            
    size_t size;      
    size_t capacity;
} mail_heap;


int generate_mail_id();

mail_heap* create_mail_heap(size_t initial_capacity);
void delete_mail_heap(mail_heap *heap);
int is_empty_mail_heap(mail_heap *heap);
int peek_mail_heap(mail_heap *heap, mail *result);
int push_mail_heap(mail_heap *heap, mail value);
int pop_mail_heap(mail_heap *heap, mail *result);
int build_mail_heap(mail_heap *heap, mail *array, size_t array_size);
int is_equal_mail_heap(mail_heap *heap1, mail_heap *heap2);
size_t size_mail_heap(mail_heap *heap);

int is_equal_mail(mail *  m1, mail * m2);
mail * create_mail(unsigned int mail_id, char *type, int priority, 
    unsigned int sender_office_id, unsigned int recipient_office_id, char *status, char *tech_data);
#endif