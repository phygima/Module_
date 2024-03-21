#include <stdio.h>
#include <stdlib.h>


typedef float (*operation)(float, float);

float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b != 0)
        return a / b;
    else {
        printf("You cant devide by zero!\n");
        return 0;
    }
}

int main() {

    operation operations[] = {add, subtract, multiply, divide};
    char *operation_names[] = {"Add", "Substract", "Multiply", "Devide"};
    int num_operations = sizeof(operations) / sizeof(operations[0]);

    char choice;
    int operation_choice;
    float num1, num2, result;

    do {
        printf("Choice:\n");
       
        for (int i = 0; i < num_operations; i++) {
            printf("%d. %s\n", i + 1, operation_names[i]);
        }
        printf("%d. Exit\n", num_operations + 1);
        printf("Your coice: ");
        scanf(" %c", &choice);

        operation_choice = choice - '0' - 1;

        if (operation_choice >= 0 && operation_choice < num_operations) {
            printf("Enter two numbers %s: ", operation_names[operation_choice]);
            scanf("%f %f", &num1, &num2);

            result = operations[operation_choice](num1, num2);
            printf("Result: %.2f\n", result);
        } else if (choice == num_operations + 1) {
            printf("Exeting..\n");
        } else {
            printf("Invalid coice\n");
        }

    } while (choice != num_operations + 1);

    return 0;
}
