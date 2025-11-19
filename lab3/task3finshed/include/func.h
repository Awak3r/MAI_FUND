#ifndef FUNC_H
#define FUNC_H
#include "../include/opt_func.h"
#include <stddef.h>
#include <stdio.h>


typedef struct Node{
    Liver * data;
    struct Node *prev;
    struct Node *next;                                          
} Node;

typedef struct {
    Node * head;
    Node * tail;
    size_t size;
} LinkedList;


LinkedList create_list(void);
void erase_list(LinkedList *list);
void delete_list(LinkedList *list);
void push_back_list(LinkedList *list, Liver * value);
void push_front_list(LinkedList *list, Liver * value);
Liver * pop_back_list(LinkedList *list);
Liver * pop_front_list(LinkedList *list);
void insert_at_list(LinkedList *list, size_t index, Liver * value);
void delete_at_list(LinkedList *list, size_t index);
Liver * get_at_list(LinkedList *list, size_t index);
int is_equal_list(LinkedList *l1, LinkedList *l2);

LinkedList copy_list(LinkedList *source);
int read_from_file(char * filename, LinkedList * main);
void sort(LinkedList *list);
void search_by_id(LinkedList *list, unsigned int id);
void search_by_surname(LinkedList *list,  char *surname);
void search_by_first_name(LinkedList *list,  char *first_name);
void search_by_birth_date(LinkedList *list,  char *birth_date);
void print_list(LinkedList *list);
Node* find_node_by_id(LinkedList *list, unsigned int id);
int export_list_to_file(char *filename,  LinkedList *list);
#endif