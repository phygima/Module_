#ifndef BTREE_INFO_H
#define BTREE_INFO_H

#include "contact.h"
#include <stdio.h>

typedef struct Btree
{   
    Contact contact;
    struct Btree* left;
    struct Btree* right;
    
} Btree;

Btree* createNode(Contact contact);
Btree* insert(Btree* root, Contact contact);
Btree* seach_root(Btree* root, const char* last_name, const char* first_name);
void add_contact_Btree(Btree** root);
void inorder_traversal(Btree* root);
void edit_contact_Btree(Btree* root,const char* last_name, const char* first_name);
void delete_contact_Btree(Btree** root, const char* last_name, const char* first_name);
void deleteTree(Btree* root);


#endif