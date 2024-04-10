#include "add.h"
#include "divide.h"
#include "multiply.h"
#include "subtract.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef float (*operation)(float, float);


int main() {
    operation operations[] = {add, subtract, multiply, divide};
    char *operation_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    int num_operations = sizeof(operations) / sizeof(operations[0]);

    char input[100];
    float num1, num2, result;

    do {
        printf("Choice:\n");

        for (int i = 0; i < num_operations; i++) {
            printf("%d. %s\n", i + 1, operation_names[i]);
        }
        printf("%d. Exit\n", num_operations+1);
        printf("Your choice: ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "5") == 0) {
            printf("Exiting...\n");
            break;
        }

        int operation_choice = atoi(input);

        if (operation_choice >= 1 && operation_choice <= num_operations) {
            printf("Enter two numbers for %s: ", operation_names[operation_choice - 1]);
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%f %f", &num1, &num2);
            result = operations[operation_choice - 1](num1, num2);
            printf("Result: %.2f\n", result);
        } else {
            printf("Invalid choice\n");
        }

    } while (1);

    return 0;
}