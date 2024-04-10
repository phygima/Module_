#include <stdio.h>
#include "contact.h"


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


Contact* create_contact(const char *first_name, const char *last_name, const char *work_place,
                        const char *position, const char *phone, const char *email, const char *social){
    Contact* new_contact = (Contact*)malloc(sizeof(Contact));
    if(new_contact == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    strncpy(new_contact->personal_info.first_name,first_name,MAX_NAME_LENGTH);
    strncpy(new_contact->personal_info.last_name, last_name, MAX_NAME_LENGTH);
    strncpy(new_contact->personal_info.work_place, work_place, MAX_NAME_LENGTH);
    strncpy(new_contact->personal_info.position, position, MAX_NAME_LENGTH);
    strncpy(new_contact->contact_info.phone, phone, MAX_PHONE_LENGTH);
    strncpy(new_contact->contact_info.email, email, MAX_EMAIL_LENGTH);
    strncpy(new_contact->contact_info.social, social, MAX_SOCIAL_LENGTH);
    new_contact->prev = NULL;
    new_contact->next = NULL;

    return new_contact;

}


void add_contact(Contact** head_ptr, Contact* new_contact) {
    if (*head_ptr == NULL) {
        *head_ptr = new_contact;
        return;
    }

    Contact* current = *head_ptr;
    while (current-> next != NULL && strcmp(current->next->personal_info.last_name, new_contact->personal_info.last_name) > 0) {
        current = current -> next;
    }

    if(current->next == NULL) {
        current->next = new_contact;
        new_contact->prev = current;
    } else {
        new_contact->next = current->next;
        new_contact->prev = current;
        current->next->prev = new_contact;
        current->next = new_contact;
    }
 
    
}

void delete_contact(Contact** head_ptr, int index) {
    Contact* current = *head_ptr;
    int i = 0;
    while (current != NULL && i < index){
        current = current->next;
        i++;
    }
    if(current == NULL){
        printf("Contact not found\n");
        return;
    }
    if (current->prev == NULL) {
        *head_ptr = current->next;
    } else {
        current->prev->next = current->next;
    }
    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    free(current);

}


void print_contacts(Contact *head) {
    Contact* current = head;
    int i =1;
    while (current != NULL) {
        printf("Contact %d:\n", i++);
        printf("First Name: %s\n", current->personal_info.first_name);
        printf("Last Name: %s\n", current->personal_info.last_name);
        printf("Work Place: %s\n", current->personal_info.work_place);
        printf("Position: %s\n", current->personal_info.position);
        printf("Phone: %s\n", current->contact_info.phone);
        printf("Email: %s\n", current->contact_info.email);
        printf("Social: %s\n\n", current->contact_info.social);
        current = current->next;
    }
    
}

void free_contacts(Contact** head_ptr){
    Contact* current = *head_ptr;
    while (current != NULL){
        Contact* next = current->next;
        free(current);
        current = next;
    }
    *head_ptr = NULL;
    
}

void add_contact_prompt(Contact** head_ptr){
    char first_name[MAX_NAME_LENGTH], last_name[MAX_NAME_LENGTH], work_place[MAX_NAME_LENGTH], position[MAX_NAME_LENGTH], 
            phone[MAX_PHONE_LENGTH], email[MAX_EMAIL_LENGTH], social[MAX_SOCIAL_LENGTH];
    
    do{
        printf("Enter first name: ");
        fgets(first_name,MAX_NAME_LENGTH,stdin);
        clear_input_buffer();
    } while (strlen(first_name) == 1);
    do {
        printf("Enter last name: ");
        fgets(last_name, MAX_NAME_LENGTH, stdin);
        clear_input_buffer();
    } while (strlen(last_name) == 1); 

    printf("Enter work place: ");
    fgets(work_place, MAX_NAME_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter position: ");
    fgets(position, MAX_NAME_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter phone number: ");
    fgets(phone, MAX_PHONE_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter email address: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter social media profile: ");
    fgets(social, MAX_SOCIAL_LENGTH, stdin);
    clear_input_buffer();

    Contact* new_contact = create_contact(first_name, last_name, work_place, position, phone, email, social);
    add_contact(head_ptr, new_contact);
}

void delete_contact_prompt(Contact** head_ptr) {
    int index;
    printf("Enter the index of the contact to delete (1-%d): ", MAX_CONTACTS);
    scanf("%d", &index);
    clear_input_buffer();
    if (index < 1 || index > MAX_CONTACTS){
        printf("Invalid index\n");
        return;
    }
    delete_contact(head_ptr, index - 1);
}


void edit_contact(Contact *contact) {
        printf("Editing Contact:\n");
    printf("Enter first name: ");
    fgets(contact->personal_info.first_name, MAX_NAME_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter last name: ");
    fgets(contact->personal_info.last_name, MAX_NAME_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter work place: ");
    fgets(contact->personal_info.work_place, MAX_NAME_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter position: ");
    fgets(contact->personal_info.position, MAX_NAME_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter phone number: ");
    fgets(contact->contact_info.phone, MAX_PHONE_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter email address: ");
    fgets(contact->contact_info.email, MAX_EMAIL_LENGTH, stdin);
    clear_input_buffer();
    printf("Enter social media profile: ");
    fgets(contact->contact_info.social, MAX_SOCIAL_LENGTH, stdin);
    clear_input_buffer();
}

void edit_contact_prompt(Contact* head){
    int index;
    printf("Enter the index of the contact to edit (1-%d): ", MAX_CONTACTS);
    scanf("%d", &index);
    clear_input_buffer();
      if (index < 1 || index > MAX_CONTACTS) {
        printf("Invalid index\n");
        return;
    }

    Contact* current = head;
    int i = 1;
     while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Contact not found\n");
        return;
    }
    
    edit_contact(current);
}


