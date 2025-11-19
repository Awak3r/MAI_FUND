#include "../include/mail_func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int generate_mail_id() {
    static int id = 0; 
    id++;             
    return id;       
}

mail_heap* create_mail_heap(size_t initial_capacity){
    if (initial_capacity == 0) {
            initial_capacity = minimal_capacity;  
        }
        mail_heap *heap = (mail_heap*)malloc(sizeof(mail_heap));
        if (heap == NULL) {
            return NULL;
        }
        heap->mail_array = (mail *)malloc(sizeof(mail) * initial_capacity);
        if (heap->mail_array == NULL) {
            free(heap);
            return NULL;
        }
        heap->size = 0;
        heap->capacity = initial_capacity;
        return heap;
}
void delete_mail_heap(mail_heap *heap) {
    if (heap == NULL) return;
    for (size_t i = 0; i < heap->size; i++) {
        free(heap->mail_array[i].type);
        free(heap->mail_array[i].status);
        free(heap->mail_array[i].tech_data);
    }
    free(heap->mail_array);
    free(heap);
}


int is_empty_mail_heap(mail_heap *heap){
    return heap == NULL || heap->size == 0;
}

int peek_mail_heap(mail_heap *heap, mail *result){
    if (is_empty_mail_heap(heap)) {
        return -1;
    }
    *result = heap->mail_array[0];
    return 1;
}

size_t size_mail_heap(mail_heap *heap){
    return heap->size;
}

void swap_mail(mail *a, mail *b) {
    mail temp = *a;
    *a = *b;
    *b = temp;
}

size_t left_child_mail(size_t i) {
    return 2 * i + 1;
}

size_t right_child_mail(size_t i) {
    return 2 * i + 2;
}

size_t parent_mail(size_t i) {
    return (i - 1) / 2;
}

void sift_up_mail(mail_heap *heap, size_t index) {
    while (index > 0 && heap->mail_array[parent_mail(index)].priority < heap->mail_array[index].priority) {
        swap_mail(&heap->mail_array[parent_mail(index)], &heap->mail_array[index]);
        index = parent_mail(index);
    }
}

void sift_down_mail(mail_heap *heap, size_t index) {
    size_t max_index = index;
    size_t left = left_child_mail(index);
    size_t right = right_child_mail(index);
    if (left < heap->size && heap->mail_array[left].priority > heap->mail_array[max_index].priority) {
        max_index = left;
    }
    if (right < heap->size && heap->mail_array[right].priority > heap->mail_array[max_index].priority) {
        max_index = right;
    }
    if (max_index != index) {
        swap_mail(&heap->mail_array[index], &heap->mail_array[max_index]);
        sift_down_mail(heap, max_index);
    }
}


int push_mail_heap(mail_heap *heap, mail value) {
    if (heap == NULL) {
        return -1;
    }
    if (heap->size >= heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        mail *new_array = (mail *)realloc(heap->mail_array, 
                                                       sizeof(mail) * new_capacity);
        if (new_array == NULL) {
            return -1;
        }
        heap->mail_array = new_array;
        heap->capacity = new_capacity;
    }
    heap->mail_array[heap->size] = value;
    sift_up_mail(heap, heap->size);
    heap->size++;
    return 0;
}

int pop_mail_heap(mail_heap *heap, mail *result) {
    if (is_empty_mail_heap(heap)) {
        return -1;
    }
    *result = heap->mail_array[0];
    heap->size--;
    if (heap->size > 0) {
        heap->mail_array[0] = heap->mail_array[heap->size];
        sift_down_mail(heap, 0);
    }
    return 0;
}

int build_mail_heap(mail_heap *heap, mail *array, size_t array_size){
    if (heap == NULL || array == NULL || array_size == 0) {
        return -1;
    }
    if (array_size > heap->capacity) {
        mail *new_array = (mail*)realloc(
            heap->mail_array,
            sizeof(mail) * array_size
        );
        if (new_array == NULL) {
            return -1;
        }
        heap->mail_array = new_array;
        heap->capacity = array_size;
    }
    for (size_t i = 0; i < array_size; i++) {
        heap->mail_array[i] = array[i];
    }
    heap->size = array_size;
    if (heap->size > 1) {
        for (int i = (int)(heap->size / 2) - 1; i >= 0; i--) {
            sift_down_mail(heap, (size_t)i);
        }
    }
    return 0;
}

int is_equal_mail_heap(mail_heap *heap1, mail_heap *heap2){
    if (heap1 == NULL && heap2 == NULL) {
        return 1;  
    }
    if (heap1 == NULL || heap2 == NULL) {
        return 0;
    }
    if (heap1 == heap2) {
        return 1;
    }
    if (heap1->size != heap2->size) {
        return 0;
    }
    for (size_t i = 0; i < heap1->size; i++) {
        if (is_equal_mail(&heap1->mail_array[i], &heap2->mail_array[i]) == 0) {
            return 0; 
        }
    }
    return 1;  
}

int is_equal_mail(mail *  m1, mail * m2){
    if (m1->mail_id != m2->mail_id) return 0;
    if (strcmp(m1->type, m2->type) != 0) return 0;
    if (m1->priority != m2->priority) return 0;
    if (m1->sender_office_id != m2->sender_office_id) return 0;
    if (m1->recipient_office_id != m2->recipient_office_id) return 0;
    if (strcmp(m1->status, m2->status) == 0) return 0;
    if (strcmp(m1->tech_data, m2->tech_data) == 0) return 0;
    return 1;
}

mail * create_mail(unsigned int mail_id, char *type, int priority, 
    unsigned int sender_office_id, unsigned int recipient_office_id, 
    char *status, char *tech_data) {
    mail *cur = (mail *)malloc(sizeof(mail));
    if (!cur) return NULL;
    cur->mail_id = mail_id;
    cur->priority = priority;
    cur->sender_office_id = sender_office_id;
    cur->recipient_office_id = recipient_office_id;
    cur->type = (char *)malloc(strlen(type) + 1);
    if (!cur->type) {
        free(cur);
        return NULL;
    }
    strcpy(cur->type, type);
    cur->status = (char *)malloc(strlen(status) + 1);
    if (!cur->status) {
        free(cur->type);
        free(cur);
        return NULL;
    }
    strcpy(cur->status, status);
    cur->tech_data = (char *)malloc(strlen(tech_data) + 1);
    if (!cur->tech_data) {
        free(cur->type);
        free(cur->status);
        free(cur);
        return NULL;
    }
    strcpy(cur->tech_data, tech_data);
    return cur;
}


