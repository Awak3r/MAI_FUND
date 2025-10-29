#include "include/func.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc != 3){
        fprintf(stderr, "error: invalid args\n");
        return -1;
    }
    FILE *filein = fopen(argv[1], "r");
if (!filein) {
    fprintf(stderr, "error: cant open the filein\n");
    return -1;
}

FILE *fileout = fopen(argv[2], "w+");
if (!fileout) {
    fprintf(stderr, "error: cant open the fileout\n");
    fclose(filein);
    return -1;
}
    int len = 0;
    int find_len = 0;
    Student * students;
    if (read_from_file(filein, &students, &len) == -1){
        fprintf(stderr, "error: cant read from file\n");
        return -1;
    }
    int cur1, cur2;
    Student * s_cur = NULL;
    char * buf = malloc(sizeof(char) * 256);
    double sr;
    if (!buf) {
        free(students);
        return -1;
    }
    while (1) {
        start_menu();
        scanf("%d", &cur1);
        switch (cur1) {
            case 1:{
                unsigned int cur;
                fprintf(stdout, "ID: ");
                scanf("%u", &cur);
                s_cur = find_by_i(students, len, cur);
                if (!s_cur) {
                    fprintf(stderr, "error: student not found\n");
                    break;
                }
                print_struct(*s_cur);
                after_sort_menu();
                scanf("%d", &cur2);
                switch (cur2) {
                    case 1:{
                        Student *temp_array[1] = {s_cur};
                        if (write_to_file_after_sort(fileout, temp_array, 1)){
                            fprintf(stdout, "Успешно\n");
                        } else {
                            fprintf(stderr, "error: cant write to the file\n");
                        } 
                    }break;
                    case 2:{
                    }break;
                    default:{
                        fprintf(stderr, "error: invalid choise\n");
                    }break;
                }
            }break;
            case 2:{
                fprintf(stdout, "Фамилия: ");
                scanf("%255s", buf);
                Student **found = find_by_s(students, len, &find_len, buf);
                if (find_len == 0) {
                    fprintf(stderr, "error: student not found\n");
                    free(found);
                    break;
                }
                print_structs(found, find_len);
                after_sort_menu();
                scanf("%d", &cur2);
                switch (cur2) {
                    case 1:{
                        if (write_to_file_after_sort(fileout, found, find_len)){
                                fprintf(stdout, "Успешно\n");
                        } else {
                            fprintf(stderr, "error: cant write to the file\n");
                        }                    
                    }break;
                    case 2:{
                    }break;
                    default:{
                        fprintf(stderr, "error: invalid choise\n");
                    }break;
                }
                free(found);
            }break;
            case 3:{
                fprintf(stdout, "Имя: ");
                scanf("%255s", buf);
                Student **found = find_by_n(students, len, &find_len, buf);
                if (find_len == 0) {
                    fprintf(stderr, "error: student not found\n");
                    free(found);
                    break;
                }
                print_structs(found, find_len);
                after_sort_menu();
                scanf("%d", &cur2);
                switch (cur2) {
                    case 1:{
                        if (write_to_file_after_sort(fileout, found, find_len)){
                            fprintf(stdout, "Успешно\n");
                        } else {
                        fprintf(stderr, "error: cant write to the file\n");
                        }
                    }break;
                    case 2:{
                    }break;
                    default:{
                        fprintf(stderr, "error: invalid choise\n");
                    }break;
                }
                free(found);
            }break;
            case 4:{
                fprintf(stdout, "Группа: ");
                scanf("%255s", buf);
                Student **found = find_by_g(students, len, &find_len, buf);
                if (find_len == 0) {
                    fprintf(stderr, "error: student not found\n");
                    free(found);
                    break;
                }
                print_structs(found, find_len);
                after_sort_menu();
                scanf("%d", &cur2);
                switch (cur2) {
                    case 1:{
                        if (write_to_file_after_sort(fileout, found, find_len)){
                            fprintf(stdout, "Успешно\n");
                        } else {
                        fprintf(stderr, "error: cant write to the file\n");
                        }
                    }break;
                    case 2:{
                    }break;
                    default:{
                        fprintf(stderr, "error: invalid choise\n");
                    }break;
                }
                free(found);
            }break;
            case 5:{
                qsort(students, len, sizeof(Student), sort_i);
                print_structs_array(students, len);
            }break;
            case 6:{
                qsort(students, len, sizeof(Student), sort_s);
                print_structs_array(students, len);
            }break;
            case 7:{
                qsort(students, len, sizeof(Student), sort_n);
                print_structs_array(students, len);
            }break;
            case 8:{
                qsort(students, len, sizeof(Student), sort_g);
                print_structs_array(students, len);
            }break;
            case 9:{
                sr = find_sr(students, len);
                if (write_to_file_above_sr(fileout, students, len, sr)){
                fprintf(stdout, "Успешно\n");
                } else {
                    fprintf(stderr, "error: cant write to the file\n");
                }
            }break;
            case 0:{
                for (int i = 0; i < len; i++) {
                    free(students[i].surname);
                    free(students[i].name);
                    free(students[i].marks);
                    free(students[i].group);
                }
                free(students);
                free(buf);
                fclose(filein);
                fclose(fileout);
                return 0;
            }break;
            default: {
                fprintf(stderr, "error: invalid choise\n");
            break;
            }
    }

}
}