#include <stdio.h>

void add(int a, int b){
    printf("a + b = %d\n", a + b);
}

void subtract (int a, int b) {
printf("a - b = %d \n", a - b);
}

void multiply (int a, int b) {
printf("a * b = %d \n", a * b);
}

void divide(int a, int b){
    if(b !=0){
        printf("a / b = %d \n", a / b);
    }
    else printf("You cant devide by zero!");
}

void square(int a){
    printf("a^2 = %d \n", a * a);
}

int main(){

    char choice;
    int num1, num2;

    do{
        printf("\nCalculate:\n");
        printf("1. Add \n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. Square\n");  
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter two numbers to add: ");
            scanf("%d %d", &num1, &num2);
            add(num1,num2);
            break;
        case 2:
            printf("Enter two numbers to subtract: ");
            scanf("%d %d", &num1, &num2);
            subtract(num1,num2);
            break;
        case 3:
            printf("Enter two numbers to multiply: ");
            scanf("%d %d", &num1, &num2);
            multiply(num1,num2);
            break;
        case 4:
            printf("Enter two numbers to divide: ");
            scanf("%d %d", &num1, &num2);
            divide(num1,num2);
            break;
        case 5:
        printf("Enter number to square: ");
            scanf("%d", &num1);
            square(num1);

        case 6:
            printf("Exiting...\n");
            break;
        
        default:
            printf("Invalid choice.\n");
        }

    }while (choice != 6);

    return 0;
}