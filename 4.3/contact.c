#include <stdio.h>
#include "contact.h"
#include "update_contact.h"
void add_contact(Contact *contacts, int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Phonebook is full\n");
        return;
    }

    Contact new_contact;
    update_contact_details(&new_contact);

    contacts[*count] = new_contact;
    (*count)++;
}

void edit_contact(Contact *contacts, int count) {
    if (count == 0) {
        printf("No contacts to edit\n");
        return;
    }

    printf("Enter the index of the contact to edit (0-%d): ", count - 1);
    int index;
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= count) {
        printf("Invalid index\n");
        return;
    }

    Contact *contact = &contacts[index];

    char input[MAX_NAME_LENGTH];

    update_contact_details(&contact);
}

void delete_contact(Contact *contacts, int *count) {
    if (*count == 0) {
        printf("No contacts to delete\n");
        return;
    }

    printf("Enter the index of the contact to delete (0-%d): ", *count - 1);
    int index;
    scanf("%d", &index);
    getchar();  

    if (index < 0 || index >= *count) {
        printf("Invalid index\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*count)--;
}

void print_contact(Contact contact) {
    printf("First Name: %s\n", get_first_name(&contact.personal_info));
    printf("Last Name: %s\n", get_last_name(&contact.personal_info));
    printf("Work Place: %s\n", get_work_place(&contact.personal_info));
    printf("Position: %s\n", get_position(&contact.personal_info));
    printf("Phone: %s\n", get_phone(&contact.contact_info));
    printf("Email: %s\n", get_email(&contact.contact_info));
    printf("Social: %s\n", get_social(&contact.contact_info));
    printf("\n");
}

void print_contacts(Contact *contacts, int count) {
    if (count == 0) {
        printf("No contacts\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Contact %d:\n", i + 1);
        print_contact(contacts[i]);
    }
}
