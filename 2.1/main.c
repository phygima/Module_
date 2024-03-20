#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100

struct Contact {
    char first_name[50];
    char last_name[50];
    char sur_name[50];
    char job_title[50]; 
    char phone[15];
    char email [50];
    char social [50];
    char profile_msg [50];
};

struct Contact contacts[MAX_CONTACTS];
int num_contacts = 0;

void add_contact() {
    if (num_contacts >= MAX_CONTACTS) {
        printf("Contact book is full.\n");
        return;
    }

    do {
        printf("Enter First name: ");
        scanf("%s", contacts[num_contacts].first_name);
        printf("Enter Last name: ");
        scanf("%s", contacts[num_contacts].last_name);

        if (strlen(contacts[num_contacts].first_name) == 0 || strlen(contacts[num_contacts].last_name) == 0) {
            printf("Last name and First Name must be filled in!\n");
        }
    } while (strlen(contacts[num_contacts].first_name) == 0 || strlen(contacts[num_contacts].last_name) == 0);

    printf("Enter Surname: ");
    scanf("%s", contacts[num_contacts].sur_name);
    printf("Enter job title: ");
    scanf("%s", contacts[num_contacts].job_title);
    printf("Enter phone: ");
    scanf("%s", contacts[num_contacts].phone);
    printf("Enter email: ");
    scanf("%s", contacts[num_contacts].email);
    printf("Enter social media: ");
    scanf("%s", contacts[num_contacts].social);
    printf("Enter profile in message: ");
    scanf("%s", contacts[num_contacts].profile_msg);

    num_contacts++;
}

void show_contacts() {
    printf("%-15s%-15s%-15s%-25s%-15s%-25s%-10s%-10s\n", "Last Name", "First Name", "Surname",
     "Job Title", "Phone", "Email", "Social", "Profile Msg");

    for (int i = 0; i < num_contacts; i++) {
        printf("%-15s%-15s%-15s%-25s%-15s%-25s%-10s%-10s\n",
            contacts[i].last_name,
            contacts[i].first_name,
            contacts[i].sur_name,
            contacts[i].job_title,
            contacts[i].phone,
            contacts[i].email,
            contacts[i].social,
            contacts[i].profile_msg);
    }
}

void edit_contact() {
    char edit_first_name[50];
    char edit_last_name[50];

    printf("Enter the First name of the contactyou want to edit: ");
    scanf("%s", edit_first_name);
    printf("Enter the Last name of the contactyou want to edit: ");
    scanf("%s", edit_last_name);

    for(int i=0; i < num_contacts; i++){

        if(strcmp(edit_last_name, contacts[i].last_name) == 0 && 
           strcmp(edit_first_name, contacts[i].first_name) == 0){
            printf("Enter new First name: ");
            scanf("%s", contacts[i].first_name);
            printf("Enter new Last name: ");
            scanf("%s", contacts[i].last_name);
            printf("Enter new Surname: ");
            scanf("%s", contacts[i].sur_name);
            printf("Enter new job title: ");
            scanf("%s", contacts[i].job_title);
            printf("Enter new phone: ");
            scanf("%s", contacts[i].phone);
            printf("Enter new email: ");
            scanf("%s", contacts[i].email);
            printf("Enter new social: ");
            scanf("%s", contacts[i].social);
            printf("Enter new profile messenger: ");
            scanf("%s", contacts[i].profile_msg);

            printf("Contact edited.\n");
            return;
        }

    }
    printf("Contact not found.\n");
}

void delete_contact() {
    char del_first_name[50];
    char del_last_name[50];

    printf("Enter the First name of the contact you want to delete: ");
    scanf("%s", del_first_name);
    printf("Enter the Last name of the contact you want to delete: ");
    scanf("%s", del_last_name);

    for (int i = 0; i < num_contacts; i++) {

        if (strcmp(del_first_name, contacts[i].first_name) == 0 &&
            strcmp(del_last_name, contacts[i].last_name) == 0) {
                
                for(int j=i; j < num_contacts-1;j++){
                    
                    contacts[j]=contacts[j+1];
                    
                }

                num_contacts--;
                printf("Contact delited.\n");
                return;
            }
    }
    printf("Contact not found.\n");
}

int main() {
   int choice;

   do{
    printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Show Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_contact();
            break;
        case 2:
            show_contacts();
            break;
        case 3:
            edit_contact();
            break;
        case 4:
            delete_contact();
            break;
        case 5:
            printf("Exiting...\n");
            break;
        
        default:
            printf("Invalid choice.\n");
        }
   } while(choice!=5);
    return 0;
}
