#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>

#define SHMSZ 1024

volatile sig_atomic_t signal_received = 0;

void sigint_handler(int signum){
    printf("Proccess is done.\n");
    signal_received = 1;
}

int main(){
    signal(SIGINT, sigint_handler);

    const char* name = "/shm_exmp";
    int shm_fd;
    int *shm;
    int min, max, num;
    int count = 0;

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if(shm_fd < 1) {
        perror("shm_open");
        exit(1);
    }

    if(ftruncate(shm_fd, SHMSZ) ==  -1 ){
        perror("ftruncate");
        exit(1);
    }

    shm = (int *) mmap(0, SHMSZ, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
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