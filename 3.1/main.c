#include "all_permissions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char choice;

    // (1)
    printf("Do you want to enter permission in DIGITAL(d), LETTER(l), or BIT(b) format? (d/l/b): ");
    scanf(" %c", &choice);
    getchar();

    if (choice == 'd' || choice == 'D') {
        mode_t new_mode;
        printf("Enter the permission in digital format: ");
        scanf("%o", &new_mode);

        printf("Show permission in bit format:\n");
        bit_permissions(new_mode);
    }
    else if (choice == 'l' || choice == 'L') {
        char input[100];
        printf("Enter the permission in letter format: ");
        fgets(input, sizeof(input), stdin);

        printf("Show permission in bit format:\n");
        bit_permissions(letter_permissions(input));
    }
    else if (choice == 'b' || choice == 'B') {
        char bit_input[10];
        printf("Enter the permission in bit format (9 bits): ");
        fgets(bit_input, sizeof(bit_input), stdin);

        // Convert bit representation to mode_t
        mode_t bit_mode = strtol(bit_input, NULL, 2);

        printf("Show permission in letter format:\n");
        display_permissions(bit_mode);
    }

    // (2)
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error: info of file not access");
        return 1;
    }

    printf("File permission of %s:\n", filename);
    display_permissions(file_stat.st_mode);

    // (3)
    printf("Do you wish to change file permission? (y/n): ");
    scanf(" %c", &choice);
    getchar();

    if (choice == 'y' || choice == 'Y') {
        printf("Do you wish to change file permission in DIGITAL(d), LETTER(l), or BIT(b) format? (d/l/b): ");
        scanf(" %c", &choice);
        getchar();

        if (choice == 'd' || choice == 'D') {
            mode_t new_mode;
            printf("Enter the new file permission in digit format: \n");
            scanf("%o", &new_mode);
            printf("Changed file permission:\n");
            display_permissions(new_mode);
        }
        else if (choice == 'l' || choice == 'L') {
            printf("Enter the new file permission in letter format: \n");
            char let_str[10];
            fgets(let_str, sizeof(let_str), stdin);
            printf("Changed file permission:\n");
            display_permissions(let_format(let_str));
        }
        else if (choice == 'b' || choice == 'B') {
            printf("Enter the new file permission in bit format (9 bits): ");
            char bit_str[10];
            fgets(bit_str, sizeof(bit_str), stdin);

            // Convert bit representation to mode_t
            mode_t new_mode = strtol(bit_str, NULL, 2);

            printf("Changed file permission:\n");
            display_permissions(new_mode);
        }
    }

    return 0;
}