#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "contact.h"
#include "update_contact.h"

int strcompare(const char* str1, const char* str2){
    int last_name_comp = strcmp(str1, str2);
    if(last_name_comp == 0){
        return last_name_comp;
    } else {
        return last_name_comp < 0 ? -1 : 1;
    }
}

Btree* createNode(Contact contact){
    Btree* newNode =(Btree*)malloc(sizeof(Btree));
    if(newNode!= NULL){
        newNode->contact = contact;
    newNode->left = NULL;
    newNode->right = NULL;
    }
    return newNode;
}

Btree* insert(Btree* root, Contact contact){
    if(root == NULL){
        return createNode(contact);
    }
    int comp_res = strcompare(contact.personal_info.last_name, root->contact.personal_info.last_name);
    if(comp_res < 0 ||
    (comp_res == 0 && 
     strcompare(contact.personal_info.first_name, root->contact.personal_info.first_name) < 0)){
        root->left = insert(root->left,contact);
     }
     else if(comp_res == 0 && 
     strcompare(contact.personal_info.first_name, root->contact.personal_info.first_name) == 0){
        root->contact = contact;
        
     } else {
        root->right = insert(root->right, contact);
     }

    return root;
}


Btree* search_root(Btree* root, const char* last_name, const char* first_name){
    if (root == NULL || (strcompare(last_name, root->contact.personal_info.last_name) == 0 &&
                         strcompare(first_name, root->contact.personal_info.first_name) == 0)) {
        return root;
    }

    int comp_result = strcompare(last_name, root->contact.personal_info.last_name);
       if (comp_result < 0 ||
        (comp_result == 0 &&
         strcompare(first_name, root->contact.personal_info.first_name) < 0)) {
        return search_root(root->left, last_name, first_name);
    } else {
        return search_root(root->right, last_name, first_name);
    }
}

void inorder_traversal(Btree* root){
    if (root != NULL){
        inorder_traversal(root->left);
        print_contact(root->contact);
        inorder_traversal(root->right);
    }
}



void add_contact_Btree(Btree** root) {
    Contact new_contact;

    update_contact_details(&new_contact);
    
    *root = insert(*root, new_contact);
}


void edit_contact_Btree(Btree* root, const char* last_name, const char* first_name) {
    Btree* node = search_root(root, last_name, first_name);
    if (node == NULL) {
        printf("Contact not found.\n");
        return;
    }

     printf("Contact is found. Updating the info...\n");
     update_contact_details(&(node->contact));
}




void delete_contact_Btree(Btree** root, const char* last_name, const char* first_name) {
    Btree *parent = NULL;
    Btree *current = *root;

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

    if (current == NULL) {
        printf("Contact not found.\n");
        return;
    }

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

void deleteTree(Btree* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}