#include <stdio.h>
#include "contact.h"

void add_contact(Contact *contacts, int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Phonebook is full\n");
        return;
    }

    Contact new_contact;

    printf("Enter first name: ");
    fgets(new_contact.personal_info.first_name, MAX_NAME_LENGTH, stdin);
    set_first_name(&new_contact.personal_info, new_contact.personal_info.first_name);

    printf("Enter last name: ");
    fgets(new_contact.personal_info.last_name, MAX_NAME_LENGTH, stdin);
    set_last_name(&new_contact.personal_info, new_contact.personal_info.last_name);

    printf("Enter work place: ");
    fgets(new_contact.personal_info.work_place, MAX_NAME_LENGTH, stdin);
    set_work_place(&new_contact.personal_info, new_contact.personal_info.work_place);

    printf("Enter position: ");
    fgets(new_contact.personal_info.position, MAX_NAME_LENGTH, stdin);
    set_position(&new_contact.personal_info, new_contact.personal_info.position);

    printf("Enter phone number: ");
    fgets(new_contact.contact_info.phone, MAX_PHONE_LENGTH, stdin);
    set_phone(&new_contact.contact_info, new_contact.contact_info.phone);

    printf("Enter email address: ");
    fgets(new_contact.contact_info.email, MAX_EMAIL_LENGTH, stdin);
    set_email(&new_contact.contact_info, new_contact.contact_info.email);

    printf("Enter social media profile: ");
    fgets(new_contact.contact_info.social, MAX_SOCIAL_LENGTH, stdin);
    set_social(&new_contact.contact_info, new_contact.contact_info.social);

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

    printf("Enter first name: ");
    fgets(input, MAX_NAME_LENGTH, stdin);
    set_first_name(&contact->personal_info, input);

    printf("Enter last name: ");
    fgets(input, MAX_NAME_LENGTH, stdin);
    set_last_name(&contact->personal_info, input);

    printf("Enter work place: ");
    fgets(input, MAX_NAME_LENGTH, stdin);
    set_work_place(&contact->personal_info, input);

    printf("Enter position: ");
    fgets(input, MAX_NAME_LENGTH, stdin);
    set_position(&contact->personal_info, input);

    printf("Enter phone number: ");
    fgets(input, MAX_PHONE_LENGTH, stdin);
    set_phone(&contact->contact_info, input);

    printf("Enter email address: ");
    fgets(input, MAX_EMAIL_LENGTH, stdin);
    set_email(&contact->contact_info, input);

    printf("Enter social media profile: ");
    fgets(input, MAX_SOCIAL_LENGTH, stdin);
    set_social(&contact->contact_info, input);
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
