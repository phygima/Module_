#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

volatile sig_atomic_t sigint_count = 0;

void handler(int sig){
    if(sig == SIGINT){
        sigint_count++;
        if(sigint_count >=3){
            exit(EXIT_SUCCESS);
        }
    }
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
    while (1)
    {
        fprintf(file,"%d\n",count++);
        fflush(file);
        sleep(1);
    }
    

    fclose(file);
    
    return 0;
}