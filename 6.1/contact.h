#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include "personal_info.h"
#include "contact_info.h"

typedef struct Contact{
    PersonalInfo personal_info;
    ContactInfo contact_info;
    struct Contact* prev;
    struct Contact* next;
} Contact;



Contact* create_contact(const char *first_name, const char *last_name, const char *work_place,
                        const char *position, const char *phone, const char *email, const char *social);
void add_contact(Contact** head_ptr, Contact* new_contact);                      
void delete_contact(Contact** head_ptr, int index);
void print_contacts(Contact* head);
void free_contacts(Contact** head_ptr);
void clear_input_buffer();
void add_contact_prompt(Contact** head_ptr);
void delete_contact_prompt(Contact** head_ptr);
void edit_contact(Contact *contact);
void edit_contact_prompt(Contact* head);

#endif
