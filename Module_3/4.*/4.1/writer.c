#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define CHANNEL_NAME "/tmp/my_channel"
#define SEMAPHORE_KEY 5678

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


int main() {
   
    int fd, semid;
    struct sembuf sb;
   
    semid = semget(SEMAPHORE_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1) {
        if (errno == EEXIST) {
            semid = semget(SEMAPHORE_KEY, 1, 0);
        } else {
            perror("semget");
            exit(EXIT_FAILURE);
        }
    } else {
        union semun arg;
        arg.val = 1; 
        if (semctl(semid, 0, SETVAL, arg) == -1) {
            perror("semctl");
            exit(EXIT_FAILURE);
        }
    }
    mkfifo(CHANNEL_NAME, 0666);

    fd = open(CHANNEL_NAME, O_WRONLY);
    if (fd < 0){
        perror("Erorr of opening pipe for writing");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        sb.sem_num = 0;
        sb.sem_op = -1; 
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        int num = rand() % 100;
        write(fd, &num, sizeof(num));
        printf("Number is written: %d\n", num);

        sb.sem_op = 1; 
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        sleep(1);
    }
    
    close(fd);
    semctl(semid, 0, IPC_RMID);

    
    return 0;
}


