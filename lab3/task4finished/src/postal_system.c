#include "../include/postal_system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


PostalSystem* create_postal_system(const char *log_filename) {
    PostalSystem *system = (PostalSystem*)malloc(sizeof(PostalSystem));
    if (!system) return NULL;
    system->offices = create_office_heap(MAX_OFFICES);
    if (!system->offices) {
        free(system);
        return NULL;
    }
    system->office_count = 0;
    system->log_file = fopen(log_filename, "a");
    if (!system->log_file) {
        delete_office_heap(system->offices);
        free(system);
        return NULL;
    }
    system->total_mails_delivered = 0;
    system->total_mails_undelivered = 0;
    system->total_mails_in_transit = 0;
    
    return system;
}


void destroy_postal_system(PostalSystem *system) {
    if (!system) return;
    delete_office_heap(system->offices);
    if (system->log_file) {
        fclose(system->log_file);
    }
    free(system);
}


int add_office_to_system(PostalSystem *system, post_office *office) {
    if (!system || !office) return -1;
    if (office->ID >= MAX_OFFICES) {
        return -1;
    }
    if (push_office_heap(system->offices, *office) != 0) {
        return -1;
    }
    system->office_count++;
    log_office_event(system, "Office added", office->ID);
    return 0;
}


post_office* find_office_by_id(PostalSystem *system, unsigned int id) {
    if (!system || id >= MAX_OFFICES) return NULL;
    for (size_t i = 0; i < system->offices->size; i++) {
        if (system->offices->post_office_array[i].ID == id) {
            return &system->offices->post_office_array[i];
        }
    }
    return NULL;
}


int remove_office_from_system(PostalSystem *system, unsigned int office_id) {
    if (!system) return -1;
    post_office *office = find_office_by_id(system, office_id);
    if (!office) return -1;
    while (!is_empty_mail_heap(office->mail_heap_array)) {
        mail m;
        pop_mail_heap(office->mail_heap_array, &m);
        if (m.sender_office_id == office_id || m.recipient_office_id == office_id) {
            if (m.status) free(m.status);
            m.status = strdup("не доставлено");
            system->total_mails_undelivered++;
            log_mail_event(system, "Mail marked undelivered (office removed)", 
                          &m, office_id, 0);
        } else {
            if (office->connection_count > 0) {
                unsigned int next_id = office->connected_offices[0];
                post_office *next = find_office_by_id(system, next_id);
                if (next && add_mail(next, &m) == 0) {
                    log_mail_event(system, "Mail redirected", &m, office_id, next_id);
                }
            }
        }
    }
    system->office_count--;
    log_office_event(system, "Office removed", office_id);
    return 0;
}


int add_mail_to_system(PostalSystem *system, unsigned int office_id, mail *m) {
    if (!system || !m) return -1;
    post_office *office = find_office_by_id(system, office_id);
    if (!office) {
        fprintf(stderr, "Error: Office %u not found\n", office_id);
        return -1;
    }
    if (office->mail_heap_array->size >= office->max_capacity) {
        fprintf(stderr, "Error: Office %u is full\n", office_id);
        return -1;
    }
    if (add_mail(office, m) != 0) {
        return -1;
    }
    system->total_mails_in_transit++;
    log_mail_event(system, "Mail added", m, office_id, 0);
    return 0;
}


mail* find_mail_by_id(PostalSystem *system, unsigned int mail_id, post_office **location) {
    if (!system) return NULL;
    for (size_t i = 0; i < system->offices->size; i++) {
        post_office *office = &system->offices->post_office_array[i];
        for (size_t j = 0; j < office->mail_heap_array->size; j++) {
            mail *m = &office->mail_heap_array->mail_array[j];
            if (m->mail_id == mail_id) {
                if (location) {
                    *location = office;
                }
                return m;
            }
        }
    }
    return NULL;
}


int mark_mail_undelivered(PostalSystem *system, unsigned int mail_id) {
    if (!system) return -1;
    post_office *location = NULL;
    mail *m = find_mail_by_id(system, mail_id, &location);
    if (!m) {
        return -1;
    }
    if (m->status) free(m->status);
    m->status = strdup("не доставлено");
    system->total_mails_undelivered++;
    if (system->total_mails_in_transit > 0) {
        system->total_mails_in_transit--;
    }
    log_mail_event(system, "Mail marked undelivered", m, 
                   location ? location->ID : 0, 0);
    return 0;
}


int pickup_mail_from_system(PostalSystem *system, unsigned int mail_id, unsigned int office_id) {
    if (!system) return -1;
    post_office *office = find_office_by_id(system, office_id);
    if (!office) {
        return -1;
    }
    for (size_t i = 0; i < office->mail_heap_array->size; i++) {
        mail *m = &office->mail_heap_array->mail_array[i];
        if (m->mail_id == mail_id) {
            if (strcmp(m->status, "доставлено") != 0) {
                return -1;
            }
            log_mail_event(system, "Mail picked up", m, office_id, 0);
            for (size_t j = i; j < office->mail_heap_array->size - 1; j++) {
                office->mail_heap_array->mail_array[j] = 
                    office->mail_heap_array->mail_array[j + 1];
            }
            office->mail_heap_array->size--;
            return 0;
        }
    }
    return -1;
}


int find_next_office_on_path(PostalSystem *system, unsigned int from_id, unsigned int to_id) {
    if (from_id == to_id) return to_id;
    unsigned int queue[MAX_OFFICES];
    int front = 0, rear = 0;
    int visited[MAX_OFFICES] = {0};
    int parent[MAX_OFFICES];
    for (int i = 0; i < MAX_OFFICES; i++) {
        parent[i] = -1;
    }
    queue[rear++] = from_id;
    visited[from_id] = 1;
    while (front < rear) {
        unsigned int current = queue[front++];
        if (current == to_id) {
            unsigned int node = to_id;
            unsigned int prev_node = parent[to_id];
            while (parent[prev_node] != -1 && prev_node != from_id) {
                node = prev_node;
                prev_node = parent[prev_node];
            }
            return node;  
        }
        post_office *office = find_office_by_id(system, current);
        if (office) {
            for (size_t i = 0; i < office->connection_count; i++) {
                unsigned int neighbor = office->connected_offices[i];
                
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    parent[neighbor] = current;
                    queue[rear++] = neighbor;
                }
            }
        }
    }
    return -1;
}


void process_single_office(PostalSystem *system, post_office *office) {
    if (!office || is_empty_mail_heap(office->mail_heap_array)) {
        return;
    }
    mail current_mail;
    if (pop_mail_heap(office->mail_heap_array, &current_mail) != 0) {
        return;
    }
    if (office->ID == current_mail.recipient_office_id) {
        if (current_mail.status) free(current_mail.status);
        current_mail.status = strdup("доставлено");
        system->total_mails_delivered++;
        if (system->total_mails_in_transit > 0) {
            system->total_mails_in_transit--;
        }
        push_mail_heap(office->mail_heap_array, current_mail);
        log_mail_event(system, "Mail delivered", &current_mail, office->ID, office->ID);
        return;
    }
    int next_id = find_next_office_on_path(system, office->ID, current_mail.recipient_office_id);
    if (next_id == -1) {
        if (current_mail.status) free(current_mail.status);
        current_mail.status = strdup("не доставлено");
        system->total_mails_undelivered++;
        if (system->total_mails_in_transit > 0) {
            system->total_mails_in_transit--;
        }
        log_mail_event(system, "Mail undelivered (no path)", &current_mail, office->ID, 0);
        return;
    }
    post_office *next_office = find_office_by_id(system, next_id);
    if (!next_office) {
        push_mail_heap(office->mail_heap_array, current_mail);
        return;
    }
    if (next_office->mail_heap_array->size >= next_office->max_capacity) {
        push_mail_heap(office->mail_heap_array, current_mail);
        return;
    }
    if (add_mail(next_office, &current_mail) == 0) {
        log_mail_event(system, "Mail moved", &current_mail, office->ID, next_id);
    }
}


void process_all_mails(PostalSystem *system) {
    if (!system) return;
    for (size_t i = 0; i < system->offices->size; i++) {
        post_office *office = &system->offices->post_office_array[i];
        process_single_office(system, office);
    }
}


void log_mail_event(PostalSystem *system, const char *event, mail *m, 
                    unsigned int from_office, unsigned int to_office) {
    if (!system || !system->log_file || !m) return;
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    if (to_office == 0) {
        fprintf(system->log_file, "[%s] %s: Mail #%u (priority %d) at office %u\n",
                time_str, event, m->mail_id, m->priority, from_office);
    } else {
        fprintf(system->log_file, "[%s] %s: Mail #%u (priority %d) from %u to %u\n",
                time_str, event, m->mail_id, m->priority, from_office, to_office);
    }
    fflush(system->log_file);
}


void log_office_event(PostalSystem *system, const char *event, unsigned int office_id) {
    if (!system || !system->log_file) return;
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    fprintf(system->log_file, "[%s] %s: Office #%u\n", time_str, event, office_id);
    fflush(system->log_file);
}


int read_mappings_file(PostalSystem *system, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }
    unsigned int id1, id2;
    while (fscanf(file, "%u %u", &id1, &id2) == 2) {
        post_office *office1 = find_office_by_id(system, id1);
        post_office *office2 = find_office_by_id(system, id2);
        if (!office1) {
            int conn[] = {0};
            post_office *new_office = create_post_office(id1, 100, NULL, 0, conn);
            if (!new_office) continue;
            add_office_to_system(system, new_office);
            free(new_office); 
            office1 = find_office_by_id(system, id1);
        }
        if (!office2) {
            int conn[] = {0};
            post_office *new_office = create_post_office(id2, 100, NULL, 0, conn);
            if (!new_office) continue;
            add_office_to_system(system, new_office);
            free(new_office);
            office2 = find_office_by_id(system, id2);
        }
        
        if (office1) {
            office1->connected_offices = realloc(office1->connected_offices, 
                                                 sizeof(int) * (office1->connection_count + 1));
            office1->connected_offices[office1->connection_count++] = id2;
        }
        
        if (office2) {
            office2->connected_offices = realloc(office2->connected_offices, 
                                                 sizeof(int) * (office2->connection_count + 1));
            office2->connected_offices[office2->connection_count++] = id1;
        }
    }
    fclose(file);
    return 0;
}


void print_all_mails_to_file(PostalSystem *system, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return; 
    fprintf(file, "=== All Mails in Postal System ===\n\n");
    for (size_t i = 0; i < system->offices->size; i++) {
        post_office *office = &system->offices->post_office_array[i];
        fprintf(file, "Office #%u (capacity: %zu/%zu):\n", 
                office->ID, office->mail_heap_array->size, office->max_capacity);
        for (size_t j = 0; j < office->mail_heap_array->size; j++) {
            mail *m = &office->mail_heap_array->mail_array[j];
            fprintf(file, "  Mail #%u: Type=%s, Priority=%d, From=%u, To=%u, Status=%s\n",
                    m->mail_id, m->type, m->priority, 
                    m->sender_office_id, m->recipient_office_id, m->status);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


void print_system_status(PostalSystem *system, int mails_count) {
    printf("\n=== Postal System Status ===\n");
    printf("Total offices: %zu\n", system->office_count);
    if (system->total_mails_delivered>mails_count){
        printf("Mails delivered: %d\n", mails_count);
    } else{
        printf("Mails delivered: %zu\n", system->total_mails_delivered);
    }
    printf("Mails undelivered: %zu\n", system->total_mails_undelivered);
    printf("Mails in transit: %zu\n", system->total_mails_in_transit);
    printf("===========================\n\n");
}


void print_menu() {
    printf("\n=== Почтовый сервис ===\n");
    printf("1. Добавить отделение\n");
    printf("2. Удалить отделение\n");
    printf("3. Добавить письмо\n");
    printf("4. Забрать письмо\n");
    printf("5. Список всех писем (файл)\n");
    printf("6. Статус системы\n");
    printf("7. Считать дамп писем\n");
    printf("8. Выход\n");
    printf("Выбор: ");
}


int load_mails_from_file(PostalSystem *system, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "error: Cannot open mails file\n");
        return -1;
    }
    char line[minimal_length];
    int loaded_count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }
        unsigned int mail_id, sender_id, recipient_id;
        int priority;
        char type[minimal_length], status[minimal_length], tech_data[minimal_length];
        int parsed = sscanf(line, "%u|%255[^|]|%d|%u|%u|%255[^|]|%511[^\n]",
                           &mail_id, type, &priority, &sender_id, 
                           &recipient_id, status, tech_data);
        
        if (parsed != 7) {
            continue;
        }
        post_office *sender_office = find_office_by_id(system, sender_id);
        if (!sender_office) {
            fprintf(stderr, "error: cant add mail to invisible office\n");
            continue;
        }
        post_office *recipient_office = find_office_by_id(system, recipient_id);
        if (!recipient_office) {
            fprintf(stderr, "error: cant add mail to invisible office\n");
            continue;
        }
        mail *m = create_mail(mail_id, type, priority, sender_id, 
                             recipient_id, status, tech_data);
        if (!m) {
            fprintf(stderr, "error: failed to create mail\n");
            continue;
        }
        if (add_mail_to_system(system, sender_id, m) != 0) {
            fprintf(stderr, "Warning: Failed to add mail to office\n");
            free(m->type);
            free(m->status);
            free(m->tech_data);
            free(m);
            continue;
        }
        free(m);  
        loaded_count++;
    }
    fclose(file);
    return loaded_count;
}
