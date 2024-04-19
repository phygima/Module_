#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float calculateSquareArea(float side) {
    return side * side;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <side1> <side2> ...\n", argv[0]);
        return 1;
    }

    int numSquares = argc - 1;

    pid_t pid = fork();

    if (pid == 0) { // Дочерний процесс
        float totalArea = 0.0;
        for (int i = 1; i <= numSquares / 2; ++i) {
            float side = atof(argv[i]);
            totalArea += calculateSquareArea(side);
        }
        printf("The child process is done. Total area: %.2f\n", totalArea);
    } else if (pid > 0) { // Родительский процесс
        float totalArea = 0.0;
        for (int i = numSquares / 2 + 1; i <= numSquares; ++i) {
            float side = atof(argv[i]);
            totalArea += calculateSquareArea(side);
        }
       // wait(NULL); 
        printf("The parent process is done. Total area: %.2f\n", totalArea);
    } else { 
        perror("fork");
        return 1;
    }

    return 0;
}
