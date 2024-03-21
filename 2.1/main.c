#include <stdio.h>
#include "contact.h"

int main() {
    Contact contacts[MAX_CONTACTS];
    int count = 0;
    char choice;

    do {
        printf("Menu:\n");
        printf("1. Add contact\n");
        printf("2. Edit contact\n");
        printf("3. Delete contact\n");
        printf("4. Print contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar(); // Consume newline character

        switch(choice) {
            case '1':
                add_contact(contacts, &count);
                break;
            case '2':
                edit_contact(contacts, count);
                break;
            case '3':
                delete_contact(contacts, &count);
                break;
            case '4':
                print_contacts(contacts, count);
                break;
            case '5':
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != '5');

    return 0;
}
