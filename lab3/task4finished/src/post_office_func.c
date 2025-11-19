#include "../include/post_office_func.h"
#include "../include/mail_func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


office_heap* create_office_heap(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = minimal_capacity;  
    }
    office_heap *heap = (office_heap*)malloc(sizeof(office_heap));
    if (heap == NULL) {
        return NULL;
    }
    heap->post_office_array = (post_office*)malloc(sizeof(post_office) * initial_capacity);
    if (heap->post_office_array == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = initial_capacity;
    return heap;
}


void delete_office_heap(office_heap *heap) {
    if (heap == NULL) {
        return;
    }
    for (size_t i = 0; i < heap->size; i++){
        delete_post_office(&heap->post_office_array[i]);
    }
    free(heap->post_office_array);
    free(heap);
}


int is_empty_office_heap(office_heap *heap) {
    return heap == NULL || heap->size == 0;
}


int peek_office_heap(office_heap *heap, post_office *result) {
    if (is_empty_office_heap(heap)) {
        return -1;
    }
    *result = heap->post_office_array[0];
    return 1;
}


size_t size_office_heap(office_heap *heap){
    return heap->size;
}


void swap_office(post_office *a, post_office *b) {
    post_office temp = *a;
    *a = *b;
    *b = temp;
}


size_t left_child_office(size_t i) {
    return 2 * i + 1;
}


size_t right_child_office(size_t i) {
    return 2 * i + 2;
}


size_t parent_office(size_t i) {
    return (i - 1) / 2;
}


void sift_up_office(office_heap *heap, size_t index) {
    while (index > 0 && heap->post_office_array[parent_office(index)].ID > heap->post_office_array[index].ID) {
        swap_office(&heap->post_office_array[parent_office(index)], &heap->post_office_array[index]);
        index = parent_office(index);
    }
}


void sift_down_office(office_heap *heap, size_t index) {
    size_t min_index = index;
    size_t left = left_child_office(index);
    size_t right = right_child_office(index);
    if (left < heap->size && heap->post_office_array[left].ID < heap->post_office_array[min_index].ID) {
        min_index = left;
    }
    if (right < heap->size && heap->post_office_array[right].ID < heap->post_office_array[min_index].ID) {
        min_index = right;
    }
    if (min_index != index) {
        swap_office(&heap->post_office_array[index], &heap->post_office_array[min_index]);
        sift_down_office(heap, min_index);
    }
}


int push_office_heap(office_heap *heap, post_office value) {
    if (heap == NULL) {
        return -1;
    }
    if (heap->size >= heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        post_office *new_array = (post_office*)realloc(heap->post_office_array, 
                                                       sizeof(post_office) * new_capacity);
        if (new_array == NULL) {
            return -1;
        }
        heap->post_office_array = new_array;
        heap->capacity = new_capacity;
    }
    heap->post_office_array[heap->size] = value;
    sift_up_office(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_office_heap(office_heap *heap, post_office *result) {
    if (is_empty_office_heap(heap)) {
        return -1;
    }
    *result = heap->post_office_array[0];
    heap->size--;
    if (heap->size > 0) {
        heap->post_office_array[0] = heap->post_office_array[heap->size];
        sift_down_office(heap, 0);
    }
    return 0;
}


int build_office_heap(office_heap *heap, post_office *array, size_t array_size) {
    if (heap == NULL || array == NULL || array_size == 0) {
        return -1;
    }
    if (array_size > heap->capacity) {
        post_office *new_array = (post_office*)realloc(
            heap->post_office_array,
            sizeof(post_office) * array_size
        );
        if (new_array == NULL) {
            return -1;
        }
        heap->post_office_array = new_array;
        heap->capacity = array_size;
    }
    for (size_t i = 0; i < array_size; i++) {
        heap->post_office_array[i] = array[i];
    }
    heap->size = array_size;
    if (heap->size > 1) {
        for (int i = (int)(heap->size / 2) - 1; i >= 0; i--) {
            sift_down_office(heap, (size_t)i);
        }
    }
    return 0;
}


int is_equal_office_heap(office_heap *heap1, office_heap *heap2) {
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
        if (is_equal_post_office(&heap1->post_office_array[i], &heap2->post_office_array[i]) == 0) {
            return 0; 
        }
    }
    return 1;  
}


void delete_post_office(post_office *office){
    if (!office) return;
    delete_mail_heap(office->mail_heap_array);
    free(office->connected_offices);
}


int is_equal_post_office(post_office *p1, post_office *p2){
    if (p1->ID != p2->ID) return 0;
    if (p1->max_capacity != p2->max_capacity) return 0;
    if (is_equal_mail_heap(p1->mail_heap_array, p2->mail_heap_array) == 0) return 0;
    if (p1->connection_count != p2->connection_count) return 0;
    for (size_t i = 0; i < p1->connection_count; i++){
        if (p1->connected_offices[i] != p2->connected_offices[i]) return 0;
    }
    return 1;
}


post_office* create_post_office(unsigned int ID, size_t max_capacity, 
    mail_heap *mail_heap_array, size_t connection_count, int *connected_offices) {
    post_office *cur = (post_office *)malloc(sizeof(post_office));
    if (!cur) return NULL;
    cur->ID = ID;
    cur->max_capacity = max_capacity;
    cur->mail_heap_array = create_mail_heap(max_capacity);
    if (!cur->mail_heap_array) {
        free(cur);
        return NULL;
    }
    cur->connection_count = connection_count;
    
    if (connection_count > 0) {
        cur->connected_offices = (int *)malloc(sizeof(int) * connection_count);
        if (!cur->connected_offices) {
            delete_mail_heap(cur->mail_heap_array);
            free(cur);
            return NULL;
        }
        for (size_t i = 0; i < connection_count; i++) {
            cur->connected_offices[i] = connected_offices[i];
        }
    } else {
        cur->connected_offices = NULL;
    }
    
    return cur;
}


int add_mail(post_office *p, mail *m){
    if (!p || !m) return -1;
    mail copy;
    copy.mail_id = m->mail_id;
    copy.priority = m->priority;
    copy.sender_office_id = m->sender_office_id;
    copy.recipient_office_id = m->recipient_office_id;
    copy.type = strdup(m->type);
    copy.status = strdup(m->status);
    copy.tech_data = strdup(m->tech_data);
    if (!copy.type || !copy.status || !copy.tech_data) {
        if (copy.type) free(copy.type);
        if (copy.status) free(copy.status);
        if (copy.tech_data) free(copy.tech_data);
        return -1;
    }
    return push_mail_heap(p->mail_heap_array, copy);
}


mail* get_mail(post_office *p) {
    if (!p) return NULL;
    mail *res = (mail *)malloc(sizeof(mail));
    if (!res) return NULL;
    if (pop_mail_heap(p->mail_heap_array, res) == 0) {
        return res; 
    }
    free(res);
    return NULL; 
}
