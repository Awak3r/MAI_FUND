#include "../include/func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>



int validate_struct(Student  cur){
    if (!cur.name || !cur.surname || !cur.group || !cur.marks) return -1;
    size_t s_len = strlen(cur.surname);
    size_t n_len = strlen(cur.name);
    size_t g_len = strlen(cur.group);
    if (s_len == 0 || n_len == 0 || g_len == 0) return -1;
    if (cur.id == 0) return -1;
    for (size_t i = 0; i<s_len; i++){
        if ((cur.surname[i]<'a' || cur.surname[i]>'z') && 
        (cur.surname[i]<'A' || cur.surname[i] >'Z')){
            return -1;
        }
    }
    for (size_t i = 0; i<n_len; i++){
        if ((cur.name[i]<'a' || cur.name[i]>'z') && 
        (cur.name[i]<'A' || cur.name[i] >'Z')){
            return -1;
        }
    }
    for (size_t i = 0; i<g_len; i++){
        if ((cur.group[i]<'a' || cur.group[i]>'z') && 
        (cur.group[i]<'A' || cur.group[i] >'Z') && (cur.group[i]<'0' || cur.group[i]>'9')){
            return -1;
        }
    }
    for(size_t i = 0; i < 5; i++){
    if (!((cur.marks[i] >= '1' && cur.marks[i] <= '5') || 
          (cur.marks[i] >= 'A' && cur.marks[i] <= 'F'))) {
        return -1;
    }

}

    
    return 1;
}
int read_from_file(FILE * filein, Student ** students, int * len){
    size_t len_s;
    Student cur;
    *len = 0;
    int cur_len = 10;
    *students = malloc(sizeof(Student)* cur_len);
    if (!*students) return -1;
    unsigned char a1,a2,a3,a4,a5;
    char s_buf[256], n_buf[256], g_buf[256];
    while (fscanf(filein, "%u %255s %255s %255s %c %c %c %c %c", &cur.id, \
        s_buf, n_buf, g_buf, &a1, &a2 , &a3, &a4, &a5) == 9){
        if (*len >= cur_len){
            cur_len*=2;
            Student *sstudents = realloc(*students, sizeof(Student)* cur_len);
            if (!sstudents) {
                for (int i = 0; i < *len; i++) {
                    free((*students)[i].surname);
                    free((*students)[i].name);
                    free((*students)[i].marks);
                    free((*students)[i].group);
                }
                free(*students);
                return -1;
            }
            *students = sstudents;
        }
        cur.surname = strdup(s_buf);
    cur.name = strdup(n_buf);
    cur.group = strdup(g_buf);
        cur.marks = malloc(sizeof(unsigned char) * 5);
        if (!validate_struct(cur)) {
            for (int i = 0; i < *len; i++) {
                    free((*students)[i].surname);
                    free((*students)[i].name);
                    free((*students)[i].marks);
                    free((*students)[i].group);

            }
            free(*students);
            free(cur.surname);
            free(cur.name);
            free(cur.marks);
            free(cur.group);

            return -1;
        }
        cur.marks[0] = a1;
        cur.marks[1] = a2;
        cur.marks[2] = a3;
        cur.marks[3] = a4;
        cur.marks[4] = a5;
        (*students)[(*len)++] = cur;

    }
    return 1;
}
int write_to_file_after_sort(FILE *fileout, Student **students, int len) {
    for (int i = 0; i < len; i++) {
        double sr = find_sr(students[i], 1);  
        
        if (fprintf(fileout, "%u %s %s %s %f\n", 
                    students[i]->id, 
                    students[i]->surname,
                    students[i]->name, 
                    students[i]->group, sr) < 0) {
            return -1;
        }
    }
    fflush(fileout);
    return 1;
}

int write_to_file_above_sr(FILE * fileout, Student *cur, int len, double sr){
    for (size_t i = 0; i < len; i++){
        double cur_sr = find_sr(&cur[i], 1);  
        if (cur_sr > sr){
            if (fprintf(fileout, "%s %s\n", cur[i].surname, cur[i].name) < 0){
                return -1;
            }
        }
    }    
    fflush(fileout);
    return 1;
}

void print_struct(Student  cur){
        fprintf(stdout, "=============================================================================================================================================================\n");
        fprintf(stdout, "ID: %u\nNAME: %s %s\nGROUP: %s\nMARKS: [%c, %c, %c, %c, %c]\n", 
            cur.id, cur.surname,cur.name, cur.group, cur.marks[0], cur.marks[1], cur.marks[2], cur.marks[3], cur.marks[4]);
    }

void print_structs_array(Student *students, int len) {
    for (int i = 0; i < len; i++) {
        print_struct(students[i]);
    }
}
void print_structs(Student **students, int len) {
    for (int i = 0; i < len; i++) {
        print_struct(*students[i]); 
    }
}
int sort_i(const void *a, const void *b) {
    const Student *student1 = (const Student *)a;
    const Student *student2 = (const Student *)b;
    if (student1->id < student2->id) return -1;  
    else if (student1->id > student2->id) return 1;  
    else return 0;
}
int sort_s(const void *a, const void *b) {
    const Student *student1 = (const Student *)a;
    const Student *student2 = (const Student *)b;
    return strcmp(student1->surname, student2->surname);
}
int sort_n(const void *a, const void *b) {
    const Student *student1 = (const Student *)a;
    const Student *student2 = (const Student *)b;
    return strcmp(student1->name, student2->name);
}
int sort_g(const void *a, const void *b) {
    const Student *student1 = (const Student *)a;
    const Student *student2 = (const Student *)b;
    return strcmp(student1->group, student2->group);
}

Student * find_by_i(Student * students, int len, unsigned int id){
    qsort(students, len, sizeof(Student), sort_i);
    int a = 0, b = len - 1, mid;
    while (a<=b) {
        mid = (a+b)/2;
        if (students[mid].id == id) return &students[mid];
        else if(students[mid].id>id) b= mid - 1;
        else if (students[mid].id<id) a= mid + 1;
    }
    return NULL;
}
Student ** find_by_s(Student * students, int len, int * find_len, char * surname){
    Student ** res = malloc(len * sizeof(Student*));
    size_t k = 0;
    for (size_t i = 0; i< len ; i++){
        if (strcmp(students[i].surname, surname) == 0) res[k++] = &students[i];
    }
    if (k == 0) {
        *find_len = 0;
        free(res);
        return NULL;
    }
    *find_len = k;
    return res;
}
Student ** find_by_n(Student * students, int len, int * find_len, char * name){
    Student ** res = malloc(len * sizeof(Student*));
    size_t k = 0;
    for (size_t i = 0; i< len ; i++){
        if (strcmp(students[i].name, name) == 0) res[k++] = &students[i];
    }
    if (k == 0) {
        *find_len = 0;
        free(res);
        return NULL;
    }
    *find_len = k;
    return res;
}
Student ** find_by_g(Student * students, int len, int * find_len, char * group){
    Student ** res = malloc(len * sizeof(Student*));
    size_t k = 0;
    for (size_t i = 0; i< len ; i++){
        if (strcmp(students[i].group, group) == 0) res[k++] = &students[i];
    }
    if (k == 0) {
        *find_len = 0;
        free(res);
        return NULL;
    }
    *find_len = k;
    return res;
}

double find_sr(Student * cur, int len){
    double res = 0;
    double cur_res = 0;
    for (size_t i = 0; i<len; i++){
        for (int j = 0; j<5; j++){
            if (cur[i].marks[j] >= '1' && cur[i].marks[j] <= '5'){
                cur_res+=cur[i].marks[j] - '0';
            }
            if (cur[i].marks[j] >= 'A' && cur[i].marks[j] <= 'F'){
                switch(cur[i].marks[j]){
                    case 'A': cur_res += 5; break;
                    case 'B': cur_res += 4; break;
                    case 'C': cur_res += 3; break;
                    case 'D': cur_res += 2; break;
                    case 'E': cur_res += 2; break;  
                    case 'F': cur_res += 1; break;
                }
            }
        }
        res+=cur_res/5.0;
        cur_res = 0;
    }
    res/=len;
    return res;
}
void start_menu() {
    printf("\n=== Меню ===\n");
    printf("1. Поиск по id\n");
    printf("2. Поиск по фамилии\n");
    printf("3. Поиск по имени\n");
    printf("4. Поиск по группе\n");
    printf("5. Сортировка по id\n");
    printf("6. Сортировка по фамилии\n");
    printf("7. Сортировка по имени\n");
    printf("8. Сортировка по группе\n");
    printf("9. Вывод студентов с баллом выше среднего в файл\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}
void after_sort_menu(){
    printf("\n=== Меню ===\n");
    printf("1. Вывести в трассировочный файл\n");
    printf("2. Назад\n");
    printf("Выбор: ");

}
