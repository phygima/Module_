#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include "personal_info.h"
#include "contact_info.h"

typedef struct {
    PersonalInfo personal_info;
    ContactInfo contact_info;
} Contact;

void add_contact(Contact *contacts, int *count);
void edit_contact(Contact *contacts, int count);
void delete_contact(Contact *contacts, int *count);
void print_contact(Contact contact);
void print_contacts(Contact *contacts, int count);

#endif
