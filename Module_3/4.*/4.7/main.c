#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define SHMSZ 1024

int signal_received = 0;

void sigint_handler(int signum){
    printf("Proccess is done.\n");
    signal_received = 1;
}

int main(){
    signal(SIGINT, sigint_handler);

    key_t key = 123;
    int shmid;
    int *shm;
    int min, max, num;
    int count = 0;

    if((shmid = shmget(key, SHMSZ,IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if((shm = shmat(shmid, NULL, 0)) == (int *) -1 ){
        perror("shmat");
        exit(1);
    }

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        
        while(1) {
            num = rand() % 10 + 1;
            shm[0] = num;
            for(int i = 1; i <= num; i++){
                shm[i] = rand() % 1000;
            }

        sleep(1);

        printf("Max numder: %d, Min numder: %d\n", shm[num + 1], shm[num + 2]);

        count++; 

        if(signal_received == 1){
            break;
        }
    }
    printf("Count of data sets processed: %d\n", count);
    } else {
        while (1)
        {
            num = shm[0];
            max = min = shm[1];
            for(int i = 2; i < num + 2; i++) {
                if (shm[i] > max){
                    max = shm[i];
                }
                if(shm[i] < min){
                    min = shm[i];
                }
            }
            shm[num + 1] = max;
            shm[num + 2] = min;

            shm[0] = 0;

        }
        
    }
    return 0;

}