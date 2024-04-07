#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_SOCIAL_LENGTH 50
#define MAX_CONTACTS 100

typedef struct PersonalInfo {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char middle_name[MAX_NAME_LENGTH];
    char work_place[MAX_NAME_LENGTH];
    char position[MAX_NAME_LENGTH];
} PersonalInfo;

typedef struct ContactInfo {
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char social[MAX_SOCIAL_LENGTH];
} ContactInfo;

typedef struct Contact {
    PersonalInfo personal_info;
    ContactInfo contact_info;
} Contact;

typedef struct TreeNode {
    Contact contact;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int compare_names(const char* name1, const char* name2) {
    int last_name_comparison = strcmp(name1, name2);
    if (last_name_comparison == 0) {
        return last_name_comparison;
    } else {
        return last_name_comparison < 0 ? -1 : 1;
    }
}

TreeNode* createTreeNode(Contact contact) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->contact = contact;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

TreeNode* insert(TreeNode* root, Contact contact) {
    if (root == NULL) {
        return createTreeNode(contact);
    }

    int comparison_result = compare_names(contact.personal_info.last_name, root->contact.personal_info.last_name);
    if (comparison_result < 0 ||
        (comparison_result == 0 &&
         compare_names(contact.personal_info.first_name, root->contact.personal_info.first_name) < 0)) {
        root->left = insert(root->left, contact);
    } else {
        root->right = insert(root->right, contact);
    }

    return root;
}

TreeNode* search(TreeNode* root, const char* last_name, const char* first_name) {
    if (root == NULL || (compare_names(last_name, root->contact.personal_info.last_name) == 0 &&
                         compare_names(first_name, root->contact.personal_info.first_name) == 0)) {
        return root;
    }

    int comparison_result = compare_names(last_name, root->contact.personal_info.last_name);
    if (comparison_result < 0 ||
        (comparison_result == 0 &&
         compare_names(first_name, root->contact.personal_info.first_name) < 0)) {
        return search(root->left, last_name, first_name);
    } else {
        return search(root->right, last_name, first_name);
    }
}


void print_contact(Contact contact) {
    printf("First Name: %s\n", contact.personal_info.first_name);
    printf("Last Name: %s\n", contact.personal_info.last_name);
    printf("Middle Name: %s\n", contact.personal_info.middle_name);
    printf("Work Place: %s\n", contact.personal_info.work_place);
    printf("Position: %s\n", contact.personal_info.position);
    printf("Phone: %s\n", contact.contact_info.phone);
    printf("Email: %s\n", contact.contact_info.email);
    printf("Social: %s\n", contact.contact_info.social);
    printf("\n");
}

void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        print_contact(root->contact);
        inorderTraversal(root->right);
    }
}

void add_contact(TreeNode** root) {
    Contact new_contact;
    printf("Enter first name: ");
    fgets(new_contact.personal_info.first_name, MAX_NAME_LENGTH, stdin);
    printf("Enter last name: ");
    fgets(new_contact.personal_info.last_name, MAX_NAME_LENGTH, stdin);
    printf("Enter middle name: ");
    fgets(new_contact.personal_info.middle_name, MAX_NAME_LENGTH, stdin);
    printf("Enter work place: ");
    fgets(new_contact.personal_info.work_place, MAX_NAME_LENGTH, stdin);
    printf("Enter position: ");
    fgets(new_contact.personal_info.position, MAX_NAME_LENGTH, stdin);
    printf("Enter phone number: ");
    fgets(new_contact.contact_info.phone, MAX_PHONE_LENGTH, stdin);
    printf("Enter email address: ");
    fgets(new_contact.contact_info.email, MAX_EMAIL_LENGTH, stdin);
    printf("Enter social media profile: ");
    fgets(new_contact.contact_info.social, MAX_SOCIAL_LENGTH, stdin);
    *root = insert(*root, new_contact);
}

void edit_contact(TreeNode* root, const char* last_name, const char* first_name) {
    TreeNode* node = search(root, last_name, first_name);
    if (node == NULL) {
        printf("Contact not found.\n");
        return;
    }

    printf("Enter new contact details:\n");
    printf("Enter first name: ");
    fgets(node->contact.personal_info.first_name, MAX_NAME_LENGTH, stdin);
    printf("Enter last name: ");
    fgets(node->contact.personal_info.last_name, MAX_NAME_LENGTH, stdin);
    printf("Enter middle name: ");
    fgets(node->contact.personal_info.middle_name, MAX_NAME_LENGTH, stdin);
    printf("Enter work place: ");
    fgets(node->contact.personal_info.work_place, MAX_NAME_LENGTH, stdin);
    printf("Enter position: ");
    fgets(node->contact.personal_info.position, MAX_NAME_LENGTH, stdin);
    printf("Enter phone number: ");
    fgets(node->contact.contact_info.phone, MAX_PHONE_LENGTH, stdin);
    printf("Enter email address: ");
    fgets(node->contact.contact_info.email, MAX_EMAIL_LENGTH, stdin);
    printf("Enter social media profile: ");
    fgets(node->contact.contact_info.social, MAX_SOCIAL_LENGTH, stdin);
}

void delete_contact(TreeNode** root, const char* last_name, const char* first_name) {
    TreeNode *parent = NULL;
    TreeNode *current = *root;

    // Find the node to delete
    while (current != NULL && (strcompare(last_name, current->contact.personal_info.last_name) != 0 ||
                               strcompare(first_name, current->contact.personal_info.first_name) != 0)) {
        parent = current;
        if (strcompare(last_name, current->contact.personal_info.last_name) < 0 ||
            (strcompare(last_name, current->contact.personal_info.last_name) == 0 &&
             strcompare(first_name, current->contact.personal_info.first_name) < 0)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // If the node is not found
    if (current == NULL) {
        printf("Contact not found.\n");
        return;
    }

    // If the node has no children
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            *root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
}

void deleteTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}


int main() {
    TreeNode* root = NULL;
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
                add_contact(&root);
                break;
            case '2':
                {
                    char last_name[MAX_NAME_LENGTH];
                    char first_name[MAX_NAME_LENGTH];
                    printf("Enter last name: ");
                    fgets(last_name, MAX_NAME_LENGTH, stdin);
                    printf("Enter first name: ");
                    fgets(first_name, MAX_NAME_LENGTH, stdin);
                    edit_contact(root, last_name, first_name);
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
                    delete_contact(&root, last_name, first_name);
                }
                break;
            case '4':
                printf("\nAll Contacts:\n");
                inorderTraversal(root);
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
