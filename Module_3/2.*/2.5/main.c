#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

volatile sig_atomic_t stop = 0;

void handler(int sig){
    stop = 1;
}

int main() {

    signal(SIGINT, handler);

    FILE *file = fopen("output.txt", "w");
    if(file == NULL){
        perror("File is not open.\n");
        return 1;
    }
    pid_t pid = getpid();
    printf("PID: %d\n",pid);

    int count = 0;
    while (!stop)
    {
        fprintf(file,"%d\n",count++);
        fflush(file);
        sleep(1);
    }
    

    fclose(file);
    
    return 0;
}