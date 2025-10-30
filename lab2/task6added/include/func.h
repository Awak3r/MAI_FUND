#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>

typedef struct {
    unsigned int id;
    char * name;
    char * surname;
    char * group;
    unsigned char * marks;
}Student;
int validate_struct(Student cur);
int read_from_file(FILE * filein, Student ** students, int * len);
int write_to_file_after_sort(FILE *fileout, Student **students, int len);
int write_to_file_above_sr(FILE * fileout, Student *cur ,int len, double sr);
void print_struct(Student  cur);
void print_structs(Student **students, int len);
void print_structs_array(Student *students, int len);
int sort_i(const void *a, const void *b);
int sort_s(const void *a, const void *b);
int sort_n(const void *a, const void *b);
int sort_g(const void *a, const void *b);
double find_sr(Student * cur, int len);
Student * find_by_i(Student * students, int len, unsigned int id);
Student ** find_by_s(Student * students, int len, int * find_len, char * surname);
Student ** find_by_n(Student * students, int len, int * find_len, char * name);
Student ** find_by_g(Student * students, int len, int * find_len, char * group);
void start_menu();
void after_sort_menu();

#endif