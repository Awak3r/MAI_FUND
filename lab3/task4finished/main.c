#include "include/mail_func.h"
#include "include/post_office_func.h"
#include "include/postal_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "error: need mapping file to work\n");
        return -1;
    }
    const char *log_file = (argc >= 3) ? argv[2] : "postal_log.txt";
    PostalSystem *system = create_postal_system(log_file);
    if (!system) {
        fprintf(stderr,"error: cant allocate memory!\n");
        return -1;
    }
    if (read_mappings_file(system, argv[1]) != 0) {
        fprintf(stderr,"error: cant read mapping file\n");
        destroy_postal_system(system);
        return -1;
    }
    int running = 1;
    int mails_count;
    while (running) {
        process_all_mails(system);
        print_menu();
        int choice = 0;
        scanf("%d", &choice);
        getchar(); 
        switch (choice){
            case 1: {
                unsigned int id, max_cap, num_conn;
                printf("ID отделения: ");
                scanf("%u", &id); getchar();
                printf("Максимальная вместимость: ");
                scanf("%u", &max_cap); getchar();
                printf("Кол-во связей: ");
                scanf("%u", &num_conn); getchar();
                int *connected = malloc(num_conn * sizeof(int));
                if (!connected) {
                    fprintf(stderr, "error: memory allocation failed\n");
                    break;
                }
                for (unsigned int i = 0; i < num_conn; ++i) {
                    printf("ID связанного отделения #%u: ", i + 1);
                    scanf("%d", &connected[i]); getchar();
                }
                post_office *off = create_post_office(id, max_cap, NULL, num_conn, connected);
                free(connected);
                if (!off || add_office_to_system(system, off) != 0) {
                    fprintf(stderr, "error: cant add office\n");
                    if (off) {
                        delete_post_office(off);
                        free(off);
                    }
                } else {
                    free(off);  
                    printf("Отделение добавлено!\n");
                }
            } break;
            case 2: { 
                unsigned int id;
                printf("ID удаляемого отделения: ");
                scanf("%u", &id); getchar();
                if (remove_office_from_system(system, id) == 0)
                    printf("Успешно!\n");
                else
                    fprintf(stderr,"error: cant delete office\n");
            } break;
            case 3: { 
                char type[minimal_length], status[minimal_length], tech_data[minimal_length];
                unsigned int sender, recipient;
                int priority;
                printf("Тип письма (обычное/срочное): ");
                fgets(type, minimal_length, stdin); 
                type[strcspn(type, "\n")] = 0;
                printf("Приоритет: ");
                scanf("%d", &priority); getchar();
                printf("ID отделения отправителя: ");
                scanf("%u", &sender); getchar();
                printf("ID отделения получателя: ");
                scanf("%u", &recipient); getchar();
                printf("Технические данные: ");
                fgets(tech_data, minimal_length, stdin); 
                tech_data[strcspn(tech_data, "\n")] = 0;
                strcpy(status, "в пути");
                int mail_id = generate_mail_id();
                mail *m = create_mail(mail_id, type, priority, sender, recipient, status, tech_data);
                if (!m) {
                    fprintf(stderr, "error: cant create mail\n");
                } else if (add_mail_to_system(system, sender, m) != 0) {
                    fprintf(stderr, "error: cant add mail\n");
                    free(m->type);
                    free(m->status);
                    free(m->tech_data);
                    free(m);
                } else {
                    free(m->type);
                    free(m->status);
                    free(m->tech_data);
                    free(m);
                    printf("Успешно!\n");
                    mails_count++;
                }
            } break;
            case 4: { 
                unsigned int mail_id, office_id;
                printf("ID письма: ");
                scanf("%u", &mail_id); getchar();
                printf("ID отделения: ");
                scanf("%u", &office_id); getchar();
                if (pickup_mail_from_system(system, mail_id, office_id) == 0)
                    printf("Успешно!\n");
                else
                    fprintf(stderr,"error: cant pickup mail\n");
            } break;
            case 5: {
                char filename[minimal_length];
                printf("Имя выходного файла: ");
                fgets(filename, minimal_length, stdin); 
                filename[strcspn(filename, "\n")] = 0;
                print_all_mails_to_file(system, filename);
                printf("Успешно!\n");
            } break;
            case 6: { 
                print_system_status(system, mails_count);
            } break;
            case 7: {
                char filein[minimal_length];
                printf("Имя входного файла: ");
                fgets(filein, minimal_length, stdin); 
                filein[strcspn(filein, "\n")] = 0;
                int readed = load_mails_from_file(system, filein);
                if (readed > 0) {
                    printf("%d писем добавлено в систему\n", readed);
                    mails_count+= readed;
                } else {
                    fprintf(stderr, "error: cant load mails\n");
                }
            } break;
            case 8: {
                running = 0;
            } break;
            default: {
                fprintf(stderr, "error: invalid choice\n");
            }
        }
    }
    destroy_postal_system(system);
    return 0;
}
