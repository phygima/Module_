#include <divide.h>

float divide(float a, float b) {
    if (b != 0)
        return a / b;
    else {
        printf("You cant devide by zero!\n");
        return 0;
    }
}