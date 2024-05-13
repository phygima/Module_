#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_NUMBERS 100

#define SEM_KEY 1234

int sem_id;
int numbers[MAX_NUMBERS];
int num_count;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void write_to_file() {
    FILE *file = fopen("numbers.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_count; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);
}

void read_from_file(int num_integers) {
    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    num_count = 0;
    while (fscanf(file, "%d", &numbers[num_count]) != EOF && num_count < num_integers) {
        num_count++;
    }
    fclose(file);
}

void parent_signal_handler(int sig) {
    if (sig == SIGUSR1) {
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1; // Lock
        sem_op.sem_flg = 0;
        if (semop(sem_id, &sem_op, 1) == -1) {
            perror("semop lock");
            exit(EXIT_FAILURE);
        }
        printf("Parent: file locked for writing\n");
    } else if (sig == SIGUSR2) {
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = 1; // Unlock
        sem_op.sem_flg = 0;
        if (semop(sem_id, &sem_op, 1) == -1) {
            perror("semop unlock");
            exit(EXIT_FAILURE);
        }
        printf("Parent: file unlocked for writing\n");
    }
}

void child_signal_handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Child: file locked...Waiting\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_integers>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_integers = atoi(argv[1]);
    if (num_integers <= 0 || num_integers > MAX_NUMBERS) {
        fprintf(stderr, "Invalid number of integers\n");
        return EXIT_FAILURE;
    }

    sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        return EXIT_FAILURE;
    }

    union semun sem_arg;
    sem_arg.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_arg) == -1) {
        perror("semctl SETVAL");
        return EXIT_FAILURE;
    }

    pid_t pid;
    signal(SIGUSR1, parent_signal_handler);
    signal(SIGUSR2, parent_signal_handler);

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {

        signal(SIGUSR1, child_signal_handler);

        while (1) {
            struct sembuf sem_op;
            sem_op.sem_num = 0;
            sem_op.sem_op = -1; // Lock
            sem_op.sem_flg = 0;
            if (semop(sem_id, &sem_op, 1) == -1) {
                perror("semop lock");
                exit(EXIT_FAILURE);
            }

            read_from_file(num_integers);
            printf("Child: read numbers from file:\n");
            for (int i = 0; i < num_count; i++) {
                printf("%d ", numbers[i]);
            }
            printf("\n");

            usleep(1000000);

            struct sembuf sem_op_unlock;
            sem_op_unlock.sem_num = 0;
            sem_op_unlock.sem_op = 1; // Unlock
            sem_op_unlock.sem_flg = 0;
            if (semop(sem_id, &sem_op_unlock, 1) == -1) {
                perror("semop unlock");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        for (int i = 0; i < num_integers; i++) {
            numbers[i] = rand() % 1000;
        }
        num_count = num_integers; 
        write_to_file();
        printf("Parent: generated and wrote numbers to file\n");
        while (1) {
            struct sembuf sem_op;
            sem_op.sem_num = 0;
            sem_op.sem_op = -1; // Lock
            sem_op.sem_flg = 0;
            if (semop(sem_id, &sem_op, 1) == -1) {
                perror("semop lock");
                exit(EXIT_FAILURE);
            }

            FILE *file = fopen("numbers.txt", "a");
            if (file == NULL) {
                perror("Failed to open file");
                return EXIT_FAILURE;
            }
            int random_number = rand() % 1000;
            fprintf(file, "%d\n", random_number);
            fclose(file);
            printf("Parent: added number %d to file\n", random_number);

            usleep(1000000);

            struct sembuf sem_op_unlock;
            sem_op_unlock.sem_num = 0;
            sem_op_unlock.sem_op = 1; // Unlock
            sem_op_unlock.sem_flg = 0;
            if (semop(sem_id, &sem_op_unlock, 1) == -1) {
                perror("semop unlock");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
