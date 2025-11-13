#ifndef OPT_FUNC_H
#define OPT_FUNC_H
#include <stddef.h>
#include <stdio.h>

#define MAX_LENGTH 256

typedef struct{
    unsigned int id;
    char * surname;
    char * first_name;
    char * second_name;
    char * birth_date;
    char SEX;
    double average_income;
} Liver;

Liver* create_liver();
int validate_liver(Liver * cur);
void erase_liver(Liver * cur);
int is_equal_liver( Liver *l1,  Liver *l2);
void print_menu();
void print_menu_2();
int compare_dates(char * date1, char * date2);
void edit_liver(Liver **liv1);
#endif