#include "all_permissions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

 char choice;
//(1)

    printf("Do you want to enter permission if DIGITAL(d) or LETTER(l) format? (d/l):");
    scanf(" %c", &choice);
    getchar();

    if (choice == 'd' || choice == 'D') {
        mode_t new_mode;
        printf("Enter the permission in digital format: ");
        scanf("%o", &new_mode);

        printf("Show permission in bit format:\n");
        bit_permissions(new_mode);
    }
    else if (choice == 'l' || choice == 'L')
    {
        char input[100];
        printf("Enter the permission in letter format: ");
        fgets(input, sizeof(input), stdin);
        printf("this - %s", input);

        printf("Show permission in bit format:\n");
//TO DO: dont work
        bit_permissions(letter_permissions(input));
    }
    



    //(2)
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error: info of file not access");
        return 1;
    }

    printf("File permisson %s:\n", filename);
    display_permissions(file_stat.st_mode);


//(3)
   
    printf("Do you wish to change file permission? (y/n): ");
    scanf(" %c", &choice);
    getchar();

    if (choice == 'y' || choice == 'Y') {
        
        printf("Do you wish to change file permission? (d/l/b): ");
        scanf(" %c", &choice);
        getchar();

        if(choice == 'd' || choice == 'D'){

        mode_t new_mode;
        printf("Enter the new file permission in digit format: \n");
        scanf("%o", &new_mode);
        //fgets(&new_mode, sizeof(&new_mode), stdin);
        printf("Changed file permission:\n");
        display_permissions(new_mode);

        }
        if(choice == 'l' || choice == 'L'){
            printf("Enter the new file permission in letter format: \n");
            char letf_str[2];
            fgets(letf_str, sizeof(letf_str), stdin);
            printf("Changed file permission:\n");
            display_permissions(let_format(letf_str));

        }
        if(choice == 'b' || choice == 'B'){
            printf("Enter the new file permission in bit format: ");

        }
    }

    return 0;
}