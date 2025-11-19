#include "../include/opt_func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


Liver* create_liver() {
    Liver* cur = (Liver*)malloc(sizeof(Liver));
    if (!cur) return NULL;
    cur->surname = (char*)malloc(MAX_LENGTH * sizeof(char));
    cur->first_name = (char*)malloc(MAX_LENGTH * sizeof(char));
    cur->second_name = (char*)malloc(MAX_LENGTH * sizeof(char));
    cur->birth_date = (char*)malloc(MAX_LENGTH * sizeof(char));
    cur->id = 0;
    cur->SEX = '\0';
    cur->average_income = 0.0;
    return cur;
}


int validate_liver(Liver * cur){
    size_t len = strlen(cur->first_name);
    if (len){
        for(size_t i = 0; i<len; i++){
            if (!((cur->first_name[i]>='a' && cur->first_name[i]<='z') || 
                (cur->first_name[i]>='A' && cur->first_name[i]<='Z'))) return 0;
        }
    }
    len = strlen(cur->surname);
    if (len){
        for(size_t i = 0; i<len; i++){
            if (!((cur->surname[i]>='a' && cur->surname[i]<='z') || 
            (cur->surname[i]>='A' && cur->surname[i]<='Z'))) return 0;
        }
    }
    len = strlen(cur->second_name);
    for(size_t i = 0; i<len; i++){
            if (!((cur->second_name[i]>='a' && cur->second_name[i]<='z') || 
            (cur->second_name[i]>='A' && cur->second_name[i]<='Z'))) return 0;
    }
    if (strlen(cur->birth_date) != 8)return 0;
    int day = (cur->birth_date[0] - '0') * 10 + (cur->birth_date[1] - '0');
    int month = (cur->birth_date[2] - '0') * 10 + (cur->birth_date[3] -'0');
    int year = (cur->birth_date[4] - '0') * 1000 + (cur->birth_date[5] - '0') * 100 + 
        (cur->birth_date[6] - '0') * 10 + (cur->birth_date[7] - '0');
    if (!(day<=31 ||month<=12 || (year>=1925 && year<=2025))) return 0;
    if (cur->SEX != 'M' && cur->SEX != 'W') return 0;
    if (cur->average_income<=0) return 0;
    return 1;
}

void erase_liver(Liver * cur){
    if (!cur) return;
    free(cur->surname);
    cur->surname = NULL;
    free(cur->first_name);
    cur->first_name = NULL;
    free(cur->second_name);
    cur->second_name = NULL;
    free(cur->birth_date);
    cur->birth_date = NULL;
    cur->id = 0;
    cur->SEX = '\0';
    cur->average_income = 0.0;
}

int is_equal_liver( Liver *l1,  Liver *l2){
    if (!l1 || !l2) {
        return l1 == l2;  
    }
    if (l1->id != l2->id) return 0;
    if (l1->SEX != l2->SEX) return 0;
    if (l1->average_income != l2->average_income) return 0;
    if (strcmp(l1->surname, l2->surname) != 0) return 0;
    if (strcmp(l1->first_name, l2->first_name) != 0) return 0;
    if (strcmp(l1->second_name, l2->second_name) != 0) return 0;
    if (l1->birth_date && l2->birth_date) {
        if (*l1->birth_date != *l2->birth_date) return 0;
    } else if (l1->birth_date != l2->birth_date) {
        return 0;
    }
    return 1;
}


int compare_dates(char * date1, char * date2){
    int day1 = (date1[0] - '0') * 10 + (date1[1] - '0');
    int month1 = (date1[2] - '0') * 10 + (date1[3] -'0');
    int year1 = (date1[4] - '0') * 1000 + (date1[5] - '0') * 100 + 
        (date1[6] - '0') * 10 + (date1[7] - '0');
    int day2 = (date2[0] - '0') * 10 + (date2[1] - '0');
    int month2 = (date2[2] - '0') * 10 + (date2[3] -'0');
    int year2 = (date2[4] - '0') * 1000 + (date2[5] - '0') * 100 + 
        (date2[6] - '0') * 10 + (date2[7] - '0');
    if (year1 != year2) return year1 - year2;
    if (month1  != month2) return month1 - month2;
    if (day1 != day2) return day2- day1;
    return 0;
}

void edit_liver(Liver **liv1) {
    if (!liv1 || !*liv1) return;
    Liver *old = *liv1;
    char old_surname[MAX_LENGTH], old_first_name[MAX_LENGTH];
    char old_second_name[MAX_LENGTH], old_birth_date[MAX_LENGTH];
    char old_sex = old->SEX;
    double old_income = old->average_income;
    strcpy(old_surname, old->surname);
    strcpy(old_first_name, old->first_name);
    strcpy(old_second_name, old->second_name);
    strcpy(old_birth_date, old->birth_date);
    printf("Текущие данные: %u %s %s %s %s %c %.2f\n",
        old->id, old->surname, old->first_name, old->second_name,
        old->birth_date, old->SEX, old->average_income);
    printf("Введите новые данные:\n");
    char buffer[MAX_LENGTH];
    printf("Фамилия: ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(old->surname, buffer);
    }
    printf("Имя: ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(old->first_name, buffer);
    }
    printf("Отчество: ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(old->second_name, buffer);
    }
    printf("Дата рождения (ДДММГГГГ): ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(old->birth_date, buffer);
    }
    printf("Пол (M/W): ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[0] != '\n') {
        old->SEX = buffer[0];
    }
    printf("Доход: ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[0] != '\n') {
        old->average_income = atof(buffer);
    }
    if (!validate_liver(old)) {
        strcpy(old->surname, old_surname);
        strcpy(old->first_name, old_first_name);
        strcpy(old->second_name, old_second_name);
        strcpy(old->birth_date, old_birth_date);
        old->SEX = old_sex;
        old->average_income = old_income;
        fprintf(stderr, "error: invalid Liver\n");
    } else {
        fprintf(stdout, "Успешно!\n");
    }
}





void print_menu(){
    fprintf(stdout, "============================================\n");
    fprintf(stdout, "0) Вывод списка\n");
    fprintf(stdout, "1) Считать данные из файла\n");
    fprintf(stdout, "2) Поиск жителя\n");
    fprintf(stdout, "3) Изменения жителя\n");
    fprintf(stdout, "4) Добавление жителя\n");
    fprintf(stdout, "5) Выгрузка данных в файл\n");
    fprintf(stdout, "6) Отмена предыдущей операции\n");
    fprintf(stdout, "7) Выход\n");
    fprintf(stdout, "Выбор: ");
}

void print_menu_2(){
    fprintf(stdout, "============================================\n");
    fprintf(stdout, "1) Поиск по ID\n");
    fprintf(stdout, "2) Поиск по Фамилии\n");
    fprintf(stdout, "3) Поиск по Имени\n");
    fprintf(stdout, "4) Поиск по дате рождения\n");
    fprintf(stdout, "5) Назад\n");
    fprintf(stdout, "Выбор: ");
}