#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <args count>\n", argv[0]);
        return 1;
    }

    int num_numbers = atoi(argv[1]);

    int pipefd[2];
    pid_t pid;

    if(pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if(pid == -1){
        perror("fork");
        return 1;
    }

    if(pid == 0){
        close(pipefd[0]);
        srand(getpid());

        for(int i = 0; i < num_numbers; ++i){
            int random_number = rand() % 100;
            write(pipefd[1], &random_number,sizeof(int));
        }

        close(pipefd[1]);
    } else {
        close(pipefd[1]);

        FILE *file = fopen("random_numbers.txt","w");
        if (file == NULL){
            perror("fopen");
            return 1;
        }

        int number;
        printf("Random numbers:\n");
        fprintf(file, "Random numbers:\n");

        while(read(pipefd[0],&number,sizeof(int))>0){
            printf("%d\n", number);
            fprintf(file,"%d\n",number);
        }

        fclose(file);
        close(pipefd[0]);
    }

    return 0;
}