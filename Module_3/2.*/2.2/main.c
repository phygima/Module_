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

    int parent_to_child[2];
    int child_to_parent[2];
    pid_t pid;

    if(pipe(parent_to_child) == -1 || pipe(child_to_parent)== -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if(pid == -1){
        perror("fork");
        return 1;
    }

    if(pid == 0){
        close(child_to_parent[0]);
        close(parent_to_child[1]);
        srand(getpid());

        for(int i = 0; i < num_numbers; ++i){
            int random_number = rand() % 100;
            write(child_to_parent[1], &random_number,sizeof(int));

            int response;
            read(parent_to_child[0], &response,sizeof(int));
            printf("Msg from parent: %d\n",response);
        }

        close(parent_to_child[0]);
        close(child_to_parent[1]);
    } else {
        close(parent_to_child[0]); 
        close(child_to_parent[1]);

        FILE *file = fopen("random_numbers.txt","w");
        if (file == NULL){
            perror("fopen");
            return 1;
        }

        int number;
        printf("Random numbers:\n");
        fprintf(file, "Random numbers:\n");

        while(read(child_to_parent[0],&number,sizeof(int)) > 0){
            printf("%d\n", number);
            fprintf(file,"%d\n",number);

            int response = number * 2;
            write(parent_to_child[1],&response, sizeof(int));
        }

        fclose(file);
        close(child_to_parent[0]);
        close(parent_to_child[1]);
    }

    return 0;
}