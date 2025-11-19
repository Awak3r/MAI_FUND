#include "../include/func.h"
#include "../include/opt_func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

LinkedList create_list(void){
    LinkedList res;
    res.head = NULL;
    res.tail = NULL;
    res.size = 0;
    return res;
}

void erase_list(LinkedList *list){
    if (!list) return;
    Node *current = list->head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        if (current->data) {
            erase_liver(current->data);
            free(current->data);
            current->data = NULL;
        }
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_list(LinkedList *list){
    if (!list) return;
    erase_list(list);
    free(list);
}

void push_back_list(LinkedList *list, Liver * value){
    Node  * cur = (Node *)malloc(sizeof(Node));
    if (!cur) return;
    cur->next = NULL;
    cur->data = value;
    if (list->tail == NULL){
        cur->prev = NULL;
        list->head = cur;
        list->tail = cur;
    }
    else{
        cur->prev = list->tail;
        list->tail->next = cur;
        list->tail = cur;
    }
    list->size++;
}

void push_front_list(LinkedList *list, Liver * value){
    Node  * cur = (Node *)malloc(sizeof(Node));
    if (!cur) return;
    cur->prev = NULL;
    cur->data = value;
    if (list->head == NULL){
        cur->next = NULL;
        list->head = cur;
        list->tail = cur;
    } else {
        cur->next = list->head;
        list->head->prev = cur;
        list->head = cur;
    }
    list->size++;
}

Liver * pop_back_list(LinkedList *list){
    if (!list || list->tail == NULL) {
        return NULL;
    }
    Node *old_tail = list->tail;
    Liver *data = old_tail->data;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        list->tail = old_tail->prev;
        list->tail->next = NULL;
        old_tail->prev = NULL;
    }
    free(old_tail);
    list->size--;
    return data;
}

Liver * pop_front_list(LinkedList *list){
    if (!list || list->head == NULL) {
        return NULL;
    }
    Node *old_head = list->head;
    Liver *data = old_head->data;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        list->head = old_head->next;
        list->head->prev = NULL;
        old_head->next = NULL;
    }
    free(old_head);
    list->size--;
    return data;
}

void insert_at_list(LinkedList *list, size_t index, Liver  * value){
    if (!list) return;
    if (index > list->size) {
        return;
    }
    if (index == 0) {
        push_front_list(list, value);
        return;
    }
    if (index == list->size) {
        push_back_list(list, value);
        return;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        return;
    }
    new_node->data = value;    
    Node *current;
    size_t i;    
    if (index < list->size / 2) {
        current = list->head;
        for (i = 0; i < index - 1; i++) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (i = list->size - 1; i > index - 1; i--) {
            current = current->prev;
        }
    }
    Node *next_node = current->next;
    new_node->prev = current;
    new_node->next = next_node;
    current->next = new_node;
    next_node->prev = new_node;
    list->size++;
}

void delete_at_list(LinkedList *list, size_t index){
    if (!list || index >= list->size) {
        return;
    }
    if (index == 0) {
        Liver *removed = pop_front_list(list);
        if (removed) {
            erase_liver(removed);
            free(removed);
        }
        return;
    }
    if (index == list->size - 1) {
        Liver *removed = pop_back_list(list);
        if (removed) {
            erase_liver(removed);
            free(removed);
        }
        return;
    }
    Node *current;
    size_t i;
    if (index < list->size / 2) {
        current = list->head;
        for (i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
    }
    Node *prev_node = current->prev;
    Node *next_node = current->next;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    if (current->data) {
        erase_liver(current->data);
        free(current->data);
    }
    free(current);
    list->size--;
}

Liver* get_at_list( LinkedList *list, size_t index){
    if (!list || index >= list->size) {
        return NULL;
    }
    Node *current;
    size_t i;
    if (index < list->size / 2) {
        current = list->head;
        for (i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
    }
    return current->data;
}

int is_equal_list( LinkedList *l1,  LinkedList *l2){
    if (!l1 || !l2) {
        return 0;
    }
    if (l1->size != l2->size) {
        return 0;
    }
    if (l1->size == 0) {
        return 1;
    }
    Node *current1 = l1->head;
    Node *current2 = l2->head;
    while (current1 != NULL && current2 != NULL) {
        if (!is_equal_liver(current1->data, current2->data)) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return 1;
}


int read_from_file(char * filename, LinkedList * main){
    FILE *filein = fopen(filename, "r");
    if (!filein) return -1;
    int readed = 7;
    *main = create_list();
    if (!main) {
        fclose(filein);
        return -1;
    }
    while (1) {
        Liver * cur = create_liver();
        readed = fscanf(filein,"%u %255s %255s %255s %255s %c %lf", &cur->id, cur->surname, cur->first_name, cur->second_name, cur->birth_date, &cur->SEX, &cur->average_income);
        if (readed != 7) {
            free(cur->birth_date);
            free(cur->first_name);
            free(cur->second_name);
            free(cur->surname);
            free(cur);
            break;
        }
        if (validate_liver(cur)){
            push_back_list(main, cur);
        }else {
            erase_liver(cur);
            free(cur);
        }
    }
    fclose(filein);
    return 0;
}

void sort(LinkedList *list) {
    if (!list || !list->head || list->size <= 1) {
        return;
    }
    Node *sorted = NULL;  
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        if (!sorted || compare_dates(current->data->birth_date, sorted->data->birth_date) > 0) {
            current->next = sorted;
            current->prev = NULL;
            if (sorted) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
    
            Node *temp = sorted;
            while (temp->next && compare_dates(temp->next->data->birth_date, current->data->birth_date) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }
        current = next;
    }
    list->head = sorted;
    Node *temp = sorted;
    while (temp->next) {
        temp = temp->next;
    }
    list->tail = temp;
}

void search_by_id( LinkedList *list, unsigned int id) {
    if (!list || !list->head) {
        printf("Список пуст\n");
        return;
    }
    int found = 0;
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        if (cur->data->id == id) {
            printf("Найден: %u %s %s %s %s %c %.2f\n", cur->data->id, cur->data->surname, cur->data->first_name, cur->data->second_name, cur->data->birth_date, cur->data->SEX, cur->data->average_income);
            found = 1;
        }
    }
    if (!found) printf("Нет совпадений по ID\n");
}

void search_by_surname( LinkedList *list,  char *surname) {
    if (!list || !list->head) {
        printf("Список пуст\n");
        return;
    }
    int found = 0;
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->data->surname, surname) == 0) {
            printf("Найден: %u %s %s %s %s %c %.2f\n", cur->data->id, cur->data->surname, cur->data->first_name, cur->data->second_name, cur->data->birth_date, cur->data->SEX, cur->data->average_income);
            found = 1;
        }
    }
    if (!found) printf("Нет совпадений по фамилии\n");
}

void search_by_first_name( LinkedList *list,  char *first_name) {
    if (!list || !list->head) {
        printf("Список пуст\n");
        return;
    }
    int found = 0;
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->data->first_name, first_name) == 0) {
            printf("Найден: %u %s %s %s %s %c %.2f\n", cur->data->id, cur->data->surname, cur->data->first_name, cur->data->second_name, cur->data->birth_date, cur->data->SEX, cur->data->average_income);
            found = 1;
        }
    }
    if (!found) printf("Нет совпадений по имени\n");
}

void search_by_birth_date( LinkedList *list,  char *birth_date) {
    if (!list || !list->head) {
        printf("Список пуст\n");
        return;
    }
    int found = 0;
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->data->birth_date, birth_date) == 0) {
            printf("Найден: %u %s %s %s %s %c %.2f\n", cur->data->id, cur->data->surname, cur->data->first_name, cur->data->second_name, cur->data->birth_date, cur->data->SEX, cur->data->average_income);
            found = 1;
        }
    }
    if (!found) printf("Нет совпадений по дате рождения\n");
}

Node* find_node_by_id( LinkedList *list, unsigned int id) {
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        if (cur->data->id == id) return cur;
    }
    return NULL;
}


int export_list_to_file( char *filename,  LinkedList *list) {
    if (!filename || !list) return -1;
    FILE *fout = fopen(filename, "w");
    if (!fout) {
        return -1;
    }
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        Liver *liv = cur->data;
        fprintf(fout, "%u %s %s %s %s %c %.2f\n",
            liv->id, liv->surname, liv->first_name, liv->second_name,
            liv->birth_date, liv->SEX, liv->average_income);
    }
    fclose(fout);
    return 0;
}

void print_list( LinkedList *list){
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        Liver *liv = cur->data;
        fprintf(stdout, "%u %s %s %s %s %c %.2f\n",
            liv->id, liv->surname, liv->first_name, liv->second_name,
            liv->birth_date, liv->SEX, liv->average_income);
    }
}

LinkedList copy_list( LinkedList *source) {
    LinkedList new_list = create_list();
    if (!source || !source->head) {
        return new_list;
    }
    for (Node *cur = source->head; cur != NULL; cur = cur->next) {
        Liver *new_liver = create_liver();
        if (!new_liver) {
            erase_list(&new_list);
            return create_list();
        }
        new_liver->id = cur->data->id;
        strcpy(new_liver->surname, cur->data->surname);
        strcpy(new_liver->first_name, cur->data->first_name);
        strcpy(new_liver->second_name, cur->data->second_name);
        strcpy(new_liver->birth_date, cur->data->birth_date);
        new_liver->SEX = cur->data->SEX;
        new_liver->average_income = cur->data->average_income;
        push_back_list(&new_list, new_liver);
    }
    return new_list;
}

