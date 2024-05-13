#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define CHANNEL_NAME "/tmp/my_channel"
#define SEMAPHORE_NAME "/my_semaphore"

int main() {
    sem_t *sem;
    int fd;

    sem = sem_open(SEMAPHORE_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("Semaphore opening failed");
        exit(1);
    }

    fd = open(CHANNEL_NAME, O_RDONLY);
    if (fd < 0){
        perror("Erorr of opening pipe for writing");
        exit(1);
    }

    int num;
    while(read(fd, &num, sizeof(num)) > 0){
        sem_wait(sem);
        printf("Accepted number: %d\n", num);
        sem_post(sem);
    }

    
    close(fd);
    sem_close(sem);

    return 0;
}


