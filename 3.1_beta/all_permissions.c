#include "all_permissions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display_permissions(mode_t mode) {
    printf("Letter representation: ");
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    printf("Digital representation: %o\n", mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    printf("Bit representation: ");
    for (int i = 8; i >= 0; --i) {
        printf("%c", (mode & (1 << i)) ? '1' : '0');
    }
    printf("\n");
}

void bit_permissions(mode_t mode){
    for (int i = 8; i >= 0; --i) {
        printf("%c", (mode & (1 << i) ? '1' : '0'));
    }
     printf("\n");
}



mode_t letter_permissions(const char* permission_str) {
    mode_t permissions = 0;

    for (int i = 0; i < strlen(permission_str); i++) {

        if (permission_str[i] == '\n')
            continue;

        if (permission_str[i] == ' ')
            continue;


    printf("Processing character: %c\n", permission_str[i]); 


        switch (permission_str[i]) {
            case 'r':
                permissions |= S_IRUSR | S_IRGRP | S_IROTH; 
                break;
            case 'w':
                permissions |= S_IWUSR | S_IWGRP | S_IWOTH; 
                break;
            case 'x':
                permissions |= S_IXUSR | S_IXGRP | S_IXOTH; // биты для выполнения
                break;
            case '-':
                break;
            default:
                printf("Invalid permission character.\n");
                exit(1);
        }
    }

    return permissions;
}


mode_t let_format(char* permission_str){

    mode_t permissions = 0;
    int x = 0;
    int y = 1;
    int z = 2;

  while (permission_str[x] != "\0") {
    if (permission_str[x] != ' ') {
        switch (permission_str[x]) {
            case 'u':
                permissions |= S_IRUSR | S_IWUSR | S_IXUSR;
                break;
            case 'g':
                permissions |= S_IRGRP | S_IWGRP | S_IXGRP;     
                break;
            case 'o':
                permissions |= S_IROTH | S_IWOTH | S_IXOTH;
                break;
            case 'a':
                permissions |= S_IRUSR | S_IWUSR | S_IXUSR |
                               S_IRGRP | S_IWGRP | S_IXGRP |
                               S_IROTH | S_IWOTH | S_IXOTH;
                break; 

            default:
                printf("Invalid permission character.\n");
                exit(1);
        }
    }
    x++;
  }

while (permission_str[y] != '\0') {
        if (permission_str[y] != ' ') {
            switch (permission_str[y]) {
                case '-':
                    // do nothing for remove permission
                    break;
                case '+':
                    // do nothing for adding permission
                    break;
                case '=':
                    // set permissions explicitly, clear existing ones first
                    permissions &= ~(S_IRUSR | S_IWUSR | S_IXUSR |
                                     S_IRGRP | S_IWGRP | S_IXGRP |
                                     S_IROTH | S_IWOTH | S_IXOTH);
                    break;
                default:
                    printf("Invalid permission character.\n");
                    exit(1);
            }
        }
        y++;
    }

while (permission_str[z] != '\0') {
        if (permission_str[z] != ' ') {
        switch (permission_str[z]) {
            case 'r':
                permissions |= S_IRUSR | S_IRGRP | S_IROTH; 
                break;
            case 'w':
                permissions |= S_IWUSR | S_IWGRP | S_IWOTH; 
                break;
            case 'x':
                permissions |= S_IXUSR | S_IXGRP | S_IXOTH; // биты для выполнения
                break;
            case '-':
                break;
            default:
                printf("Invalid permission character.\n");
                exit(1);
        }
    }
    z++;
}
return permissions;   

}