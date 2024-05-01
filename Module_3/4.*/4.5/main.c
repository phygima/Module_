#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <semaphore.h>

#define MAX_NUMBERS 100

int file_locked;
int numbers[MAX_NUMBERS];
int num_count;
sem_t file_semaphore;


void write_to_file() {
    sem_wait(&file_semaphore);
    FILE *file = fopen("numbers.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_count; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);
    sem_post(&file_semaphore);
}


void read_from_file() {
    sem_wait(&file_semaphore);
    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    while (fscanf(file, "%d", &numbers[num_count]) != EOF && num_count < MAX_NUMBERS) {
        num_count++;
    }
    fclose(file);
    sem_post(&file_semaphore);
}
void parent_signal_handler(int sig){
    if(sig == SIGUSR1){
        file_locked = 1;
        printf("Parent: file locked\n");
    }else if(sig == SIGUSR2){
        file_locked = 0;
        printf("Parent: file unocked\n");
    }
}

void child_signal_handler(int sig){
    if(sig == SIGUSR1){
        printf("Child: file locked...Waiting\n");
    }
}


int main(int argc, char *argv[]){

    sem_init(&file_semaphore, 0, 1);

    if(argc != 2){
        fprintf(stderr, "Usage: %s <args count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_integers = atoi(argv[1]);
    if (num_integers <= 0 || num_integers > MAX_NUMBERS) {
        fprintf(stderr, "Invalid number of integers\n");
        return EXIT_FAILURE;
    }

    
    pid_t pid;
    signal(SIGUSR1,parent_signal_handler);
    signal(SIGUSR2,parent_signal_handler);


    pid = fork();

    if(pid == -1){
        perror("fork");
        return EXIT_FAILURE;
    }

    if(pid == 0){
        
        signal(SIGUSR1, child_signal_handler);

        while(1){
            while(file_locked){
                usleep(10000);
            }

            read_from_file();
            printf("Child: read numbers from file:\n");
            for (int i = 0; i < num_count; i++) {
                printf("%d ", numbers[i]);
            }
            printf("\n");

            usleep(1000000);
        }
    } else {
         for (int i = 0; i < num_integers; i++) {
            numbers[i] = rand() % 1000;
        }
        write_to_file();
        printf("Parent: generated and wrote numbers to file\n");
        while (1) {
            while (file_locked) {
                usleep(10000);
            }

            kill(pid, SIGUSR1);

            FILE *file = fopen("numbers.txt", "a");
            if (file == NULL) {
                perror("Failed to open file");
                return EXIT_FAILURE;
            }
            int random_number = rand() % 1000;
            fprintf(file, "%d\n", random_number);
            fclose(file);
            printf("Parent: added number %d to file\n", random_number);

            kill(pid, SIGUSR2);

            usleep(1000000);
        }
        }
        sem_destroy(&file_semaphore);


    return 0;
}