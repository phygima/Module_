#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <errno.h>

#define CHANNEL_NAME "/tmp/my_channel"
#define SEMAPHORE_NAME "/my_semaphore"


int main() {
    sem_t *sem;
    int fd;

    sem = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, 0666, 1);
    if(sem == SEM_FAILED) {
        perror("Semaphore failed");
        exit(1);
    }

    mkfifo(CHANNEL_NAME, 0666);

    fd = open(CHANNEL_NAME, O_WRONLY);
    if (fd < 0){
        perror("Erorr of opening pipe for writing");
        exit(1);
    }

    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        sem_wait(sem);
        int num = rand() % 100;
        write(fd, &num, sizeof(num));
        printf("Numder is writed: %d\n", num);
        sem_post(sem);
        sleep(1);
    }
    
    close(fd);
    sem_close(sem);
    sem_unlink(SEMAPHORE_NAME);
    
    return 0;
}


