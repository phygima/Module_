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
#define SEMAPHORE_KEY 1234

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


int main() {
    int semid, fd;
    struct sembuf sb;

    semid = semget(SEMAPHORE_KEY, 1, 0);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }


    fd = open(CHANNEL_NAME, O_RDONLY);
    if (fd < 0){
        perror("Erorr of opening pipe for writing");
        exit(1);
    }

    while (1) {
        sb.sem_num = 0;
        sb.sem_op = -1; 
        sb.sem_flg = SEM_UNDO;
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        int num;
        ssize_t bytes_read = read(fd, &num, sizeof(num));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0) {
            printf("End of file.\n");
            break;
        } else {
            printf("Accepted number: %d\n", num);
        }

        sb.sem_op = 1; 
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }
    }

    
    close(fd);
   

    return 0;
}


