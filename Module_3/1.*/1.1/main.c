#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void cleanup_func(){
    printf("The program had worked fine.\n");
}

int main(int argc, char *argv[]) {
    atexit(cleanup_func);

    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        printf("The child proccess provides command line args: \n");
        for(int i = 0; i < argc; i++){
            printf("Arg %d: %s\n",i,argv[i]);
        }
    }
    else{
        //wait(NULL);

         printf("The parent proccess provides command line args: \n");
        for(int i = 0; i < argc; i++){
            printf("Arg %d: %s\n",i,argv[i]);
        }

    }
   
    return 0;
    
}