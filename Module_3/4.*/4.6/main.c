#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUMBERS 100

int numbers[MAX_NUMBERS];
int num_count;
pthread_mutex_t readers_mutex;
pthread_mutex_t write_mutex;
sem_t read_sem;

void write_to_file() {
    pthread_mutex_lock(&write_mutex);
    printf("Parent: writing numbers to file\n");
    FILE *file = fopen("numbers.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_count; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);
    printf("Parent: finished writing numbers to file\n");
    pthread_mutex_unlock(&write_mutex);
}

void read_from_file() {
    pthread_mutex_lock(&readers_mutex);
    int readers_count;
    pthread_mutex_unlock(&readers_mutex);

    sem_wait(&read_sem);

    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    num_count = 0;
    while (fscanf(file, "%d", &numbers[num_count]) != EOF && num_count < MAX_NUMBERS) {
        num_count++;
    }
    fclose(file);

    sem_post(&read_sem);
}

void* child_thread(void* arg) {
    while(1){
        read_from_file();
        printf("Child: read numbers from file:\n");
        for (int i = 0; i < num_count; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        usleep(1000000);
    }
}

int main(int argc, char *argv[]){
    pthread_mutex_init(&readers_mutex, NULL);
    pthread_mutex_init(&write_mutex, NULL);
    sem_init(&read_sem, 0, 3); 
    if(argc != 2){
        fprintf(stderr, "Usage: %s <args count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_integers = atoi(argv[1]);
    if (num_integers <= 0 || num_integers > MAX_NUMBERS) {
        fprintf(stderr, "Invalid number of integers\n");
        return EXIT_FAILURE;
    }

    pthread_t child_tid;
    pthread_create(&child_tid, NULL, child_thread, NULL);

    for (int i = 0; i < num_integers; i++) {
        numbers[i] = rand() % 1000;
    }
    num_count = num_integers;
    write_to_file();
    printf("Parent: generated and wrote numbers to file\n");

    pthread_join(child_tid, NULL);

    pthread_mutex_destroy(&readers_mutex);
    pthread_mutex_destroy(&write_mutex);
    sem_destroy(&read_sem);

    return 0;
}
