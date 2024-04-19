#include <stdio.h>
#include "contact.h"

int main() {

    Contact* head = NULL;
    char choice;
    do {
        printf("Menu:\n");
        printf("1. Add contact\n");
        printf("2. Delete contact\n");
        printf("3. Edit contact\n");
        printf("4. Print contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        clear_input_buffer();

        switch(choice) {
            case '1':
                add_contact_prompt(&head);
                break;
            case '2':
                delete_contact_prompt(&head);
                break;
            case '3':
                edit_contact_prompt(head);
                break;
            case '4':
                print_contacts(head);
                break;
            case '5':
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != '5');

    free_contacts(&head);
}
