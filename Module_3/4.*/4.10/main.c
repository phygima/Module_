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

int find_min(int *arr, int num){
    int min = arr[0];
    for( int i = 1; i < num; i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}

int find_sum(int *arr, int num){
    int sum = 0;
    for( int i = 0; i < num; i++){
        sum += arr[i];
    }
    return sum;
}

double find_avg(int *arr, int num){
    if (num == 0) return 0;
    double sum = find_sum(arr, num);
    return sum / num;
}

int main(){
    signal(SIGINT, sigint_handler);

    const char* name = "/shm_exmp";
    int shm_fd;
    int *shm;
    int num;
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

    while (!signal_received) {
        num = rand() % 10 + 1;
        shm[0] = num;
        for (int i = 1; i <= num; i++) {
            shm[i] = rand() % 1000;
        }

        pid_t pid_min, pid_sum, pid_avg;
        int status;

        pid_min = fork();
        if (pid_min < 0) {
            perror("fork");
            exit(1);
        } else if (pid_min == 0) {
            int min = find_min(&shm[1], num);
            shm[num + 2] = min;
            exit(0);
        }

        pid_sum = fork();
        if (pid_sum < 0) {
            perror("fork");
            exit(1);
        } else if (pid_sum == 0) {
            int sum = find_sum(&shm[1], num);
            shm[num + 3] = sum;
            exit(0);
        }

        pid_avg = fork();
        if (pid_avg < 0) {
            perror("fork");
            exit(1);
        } else if (pid_avg == 0) {
            double avg = find_avg(&shm[1], num);
            shm[num + 4] = (int) avg;
            exit(0);
        }

        waitpid(pid_min, &status, 0);
        waitpid(pid_sum, &status, 0);
        waitpid(pid_avg, &status, 0);
 
        printf("Data count #%d:\n", count);
        printf("Min num: %d\n", shm[num + 2]);
        printf("Summary : %d\n", shm[num + 3]);
        printf("Average : %d\n\n", shm[num + 4]);

        count++;
    }
    

    return 0;

}