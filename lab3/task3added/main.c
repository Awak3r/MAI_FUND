#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/func.h"
#include "include/opt_func.h"


int main() {
    size_t operation_count = 0;
    int cur_max = MAX_LENGTH;
    LinkedList **dump = (LinkedList **)malloc(sizeof(LinkedList *) * cur_max);
    if (!dump) return 0;
    size_t dump_len = 0;
    int choise1, choise2;
    LinkedList main = create_list();
    while(1){
        if (operation_count >= cur_max){
            cur_max *= 2;
            LinkedList **dump_cur = (LinkedList **)realloc(dump, sizeof(LinkedList *) * cur_max);
            if (!dump_cur){
                for (size_t i = 0; i < dump_len; i++) {
                    erase_list(dump[i]);
                    free(dump[i]);
                }
                free(dump);
                erase_list(&main);
                return 0;
            }
            dump = dump_cur;
        }
        while (dump_len > (operation_count / 2) && dump_len > 1) {
            erase_list(dump[0]);
            free(dump[0]);
            for (size_t i = 0; i < dump_len - 1; i++) {
                dump[i] = dump[i + 1];
            }
            dump_len--;
        }
        print_menu();
        scanf("%d", &choise1);
        getchar();
        switch (choise1) {
            case 0: {
                if (main.size == 0) {
                    fprintf(stderr, "\nerror: list is empty\n");
                } else {
                    print_list(&main);
                }
            }break;
            case 1:{
                LinkedList *cur = (LinkedList *)malloc(sizeof(LinkedList));
                if (cur) {
                    *cur = copy_list(&main);
                    dump[dump_len++] = cur;
                    operation_count++;
                }
                char filein[MAX_LENGTH];
                fprintf(stdout, "\nВведите имя файла: ");
                fgets(filein, MAX_LENGTH, stdin);
                if (filein[0] != '\n') {
                    filein[strcspn(filein, "\n")] = 0;
                    if (read_from_file(filein, &main) == 0){
                        fprintf(stdout, "\nУспешно!\n");
                    } else {
                        fprintf(stderr, "\nerror: cant read the file\n");
                        if (cur) {
                            erase_list(dump[--dump_len]); 
                            free(dump[dump_len]);
                            operation_count--;
                        }
                    }
                } else {
                    if (cur) {
                        erase_list(dump[--dump_len]);
                        free(dump[dump_len]);
                        operation_count--;
                    }
                }
            }break;
            case 2:{
                print_menu_2();
                scanf("%d", &choise2);
                getchar();
                switch (choise2) {
                    case 1:{
                        fprintf(stdout, "\nID: ");
                        unsigned int cur_id;
                        scanf("%u", &cur_id);
                        getchar();
                        search_by_id(&main, cur_id);
                    }break;
                    case 2:{
                        fprintf(stdout, "\nФамилия: ");
                        char cur_surname[MAX_LENGTH];
                        fgets(cur_surname, MAX_LENGTH, stdin);
                        if (cur_surname[0] != '\n') {
                            cur_surname[strcspn(cur_surname, "\n")] = 0;
                            search_by_surname(&main, cur_surname);
                        } else {
                            fprintf(stderr, "error: invalid surname\n");
                        }
                    }break;
                    case 3:{
                        fprintf(stdout, "\nИмя: ");
                        char cur_first_name[MAX_LENGTH];
                        fgets(cur_first_name, MAX_LENGTH, stdin);
                        if (cur_first_name[0] != '\n') {
                            cur_first_name[strcspn(cur_first_name, "\n")] = 0;
                            search_by_first_name(&main, cur_first_name);
                        } else {
                            fprintf(stderr, "\nerror: invalid first_name\n");
                        }
                    }break;
                    case 4:{
                        fprintf(stdout, "\nДата рождения: ");
                        char cur_birth_date[MAX_LENGTH];
                        fgets(cur_birth_date, MAX_LENGTH, stdin);
                        if (cur_birth_date[0] != '\n') {
                            cur_birth_date[strcspn(cur_birth_date, "\n")] = 0;
                            search_by_birth_date(&main, cur_birth_date);
                        } else {
                            fprintf(stderr, "\nerror: invalid birth_date\n");
                        }
                    }break;
                    case 5:{
                    }break;
                    default:{
                        fprintf(stderr, "\nerror: invalid choice\n");
                    }break;
                }
            }break;
            case 3:{
                LinkedList *cur = (LinkedList *)malloc(sizeof(LinkedList));
                if (cur) {
                    *cur = copy_list(&main);
                    dump[dump_len++] = cur;
                    operation_count++;
                }
                unsigned int cur_id;
                fprintf(stdout, "\nВведите ID жителя: ");
                scanf("%u", &cur_id);
                getchar();
                Node *cur_liver = find_node_by_id(&main, cur_id);
                if (!cur_liver) {
                    fprintf(stderr, "\nerror: liver not found\n");
                    if (cur) {
                        erase_list(dump[--dump_len]);
                        free(dump[dump_len]);
                        operation_count--;
                    }
                    break;
                }
                edit_liver(&cur_liver->data);
            }break;
            case 4:{
                LinkedList *cur = (LinkedList *)malloc(sizeof(LinkedList));
                if (cur) {
                    *cur = copy_list(&main);
                    dump[dump_len++] = cur;
                    operation_count++;
                }
                Liver *cur_liver = create_liver();
                fprintf(stdout, "\nID: ");
                scanf("%u", &cur_liver->id);
                getchar();
                fprintf(stdout, "\nФамилия: ");
                scanf("%s", cur_liver->surname);
                fprintf(stdout, "\nИмя: ");
                scanf("%s", cur_liver->first_name);
                fprintf(stdout, "\nОтчество: ");
                scanf("%s", cur_liver->second_name);
                fprintf(stdout, "\nПол: ");
                scanf(" %c", &cur_liver->SEX);
                fprintf(stdout, "\nДата Рождения: ");
                scanf("%s", cur_liver->birth_date);
                fprintf(stdout, "\nДоход: ");
                scanf("%lf", &cur_liver->average_income);
                getchar();
                if (validate_liver(cur_liver)){
                    push_front_list(&main, cur_liver);
                    sort(&main);
                } else{
                    fprintf(stderr, "\nerror: invalid liver\n");
                    erase_liver(cur_liver);
                    free(cur_liver);
                    if (cur) {
                        erase_list(dump[--dump_len]);
                        free(dump[dump_len]);
                        operation_count--;
                    }
                }
            }break;
            case 5:{
                char filout[MAX_LENGTH];
                fprintf(stdout, "\nВведите имя файла: ");
                fgets(filout, MAX_LENGTH, stdin);
                if (filout[0] != '\n') {
                    filout[strcspn(filout, "\n")] = 0;
                    if (export_list_to_file(filout, &main) == 0){
                        fprintf(stdout, "\nУспешно!\n");
                    } else{
                        fprintf(stderr, "\nerror: cant write to file\n");
                    }
                }
            }break;
            case 6:{
                if (dump_len == 0) {
                    fprintf(stderr, "\nerror: cant undo\n");
                    break;
                }
                LinkedList *prev_state = dump[--dump_len];
                erase_list(&main);
                main = copy_list(prev_state);
                erase_list(prev_state);
                free(prev_state);
                operation_count--;
                fprintf(stdout, "\nУспешно!\n");
            }break;
            case 7:{
                for (size_t i = 0; i < dump_len; i++) {
                    erase_list(dump[i]);
                    free(dump[i]);
                }
                free(dump);
                erase_list(&main);
                return 0;
            }break;
            default:{
                fprintf(stderr, "\nerror: invalid choice\n");
            }break;
        }
    }
}
