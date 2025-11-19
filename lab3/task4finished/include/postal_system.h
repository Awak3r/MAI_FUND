#ifndef POSTAL_SYSTEM_H
#define POSTAL_SYSTEM_H

#include "post_office_func.h"
#include "mail_func.h"
#include <time.h>

#define MAX_OFFICES 1000

typedef struct {
    office_heap *offices;                    
    size_t office_count;                    
    FILE *log_file;                         
    size_t total_mails_delivered;
    size_t total_mails_undelivered;
    size_t total_mails_in_transit;
} PostalSystem;

PostalSystem* create_postal_system(const char *log_filename);
void destroy_postal_system(PostalSystem *system);
int add_office_to_system(PostalSystem *system, post_office *office);
int remove_office_from_system(PostalSystem *system, unsigned int office_id);
post_office* find_office_by_id(PostalSystem *system, unsigned int id);
int add_mail_to_system(PostalSystem *system, unsigned int office_id, mail *m);
mail* find_mail_by_id(PostalSystem *system, unsigned int mail_id, post_office **location);
int mark_mail_undelivered(PostalSystem *system, unsigned int mail_id);
int pickup_mail_from_system(PostalSystem *system, unsigned int mail_id, unsigned int office_id);
int find_next_office_on_path(PostalSystem *system, unsigned int from_id, unsigned int to_id);
void process_all_mails(PostalSystem *system);
void process_single_office(PostalSystem *system, post_office *office);
void log_mail_event(PostalSystem *system, const char *event, mail *m, 
                    unsigned int from_office, unsigned int to_office);
void log_office_event(PostalSystem *system, const char *event, unsigned int office_id);
void print_all_mails_to_file(PostalSystem *system, const char *filename);
void print_system_status(PostalSystem *system, int mails_count);
int read_mappings_file(PostalSystem *system, const char *filename);
int load_mails_from_file(PostalSystem *system, const char *filename);

#endif
