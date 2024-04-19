#include <stdio.h>
#include "btree.h"

int main() {
    Btree* root = NULL;
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
        getchar(); 

        switch(choice) {
            case '1':
                add_contact_Btree(&root);
                break;
            case '2':
                {
                    char last_name[MAX_NAME_LENGTH];
                    char first_name[MAX_NAME_LENGTH];
                    printf("Enter last name: ");
                    fgets(last_name, MAX_NAME_LENGTH, stdin);
                    printf("Enter first name: ");
                    fgets(first_name, MAX_NAME_LENGTH, stdin);
                    edit_contact_Btree(root, last_name, first_name);
                }
                break;
            case '3':
                {
                    char last_name[MAX_NAME_LENGTH];
                    char first_name[MAX_NAME_LENGTH];
                    printf("Enter last name: ");
                    fgets(last_name, MAX_NAME_LENGTH, stdin);
                    printf("Enter first name: ");
                    fgets(first_name, MAX_NAME_LENGTH, stdin);
                    delete_contact_Btree(&root, last_name, first_name);
                }
                break;
            case '4':
                printf("\nAll Contacts:\n");
                inorder_traversal(root);
                printf("\n");
                break;
            case '5':
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != '5');

    deleteTree(root);
    return 0;
}
