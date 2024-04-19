#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LEN 100
#define MAX_ARGS 10

//добавить перенаправление
//ввода-вывода (возможность записи команд вида ls | head -3 | tail -1).

void print_prompt() {
    printf(">> ");
    fflush(stdout);
}

int main() {
    
     while (1) {
        print_prompt();

        char command[MAX_COMMAND_LEN];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        char *commands[MAX_ARGS];
        char *token = strtok(command, "|");
        int command_count = 0;
        while (token != NULL && command_count < MAX_ARGS - 1) {
            commands[command_count++] = token;
            token = strtok(NULL, "|");
        }
        commands[command_count] = NULL; 

        int prev_pipe[2];
        int next_pipe[2];

        for(int i = 0; i < command_count; i++){
            char *args[MAX_ARGS];
            char *arg_token = strtok(commands[i], " ");
            int arg_count = 0;
            while(arg_token != NULL && arg_count < MAX_ARGS - 1){
                args[arg_count++] = arg_token;
                arg_token = strtok(NULL," ");
            }
            args[arg_count] = NULL;

            if (i < command_count -1){
                pipe(next_pipe);
            }

            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);

            } else if (pid == 0) {
                if(i > 0){
                    dup2(prev_pipe[0], STDIN_FILENO);
                    close(prev_pipe[0]);
                    close(prev_pipe[1]);

                }
                if(i < command_count - 1 ){
                    dup2(next_pipe[1], STDOUT_FILENO);
                    close(next_pipe[0]);
                    close(next_pipe[1]);
                }
                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            
            } else {
                if(i > 0){
                    close(prev_pipe[0]);
                    close(prev_pipe[1]);
                }
                if (i < command_count - 1){
                    prev_pipe[0] = next_pipe[0];
                    prev_pipe[1] = next_pipe[1];
                }
            
            }
        }

        for (int i = 0; i < command_count; i++) {
            wait(NULL); 
        }

    }
    
    return 0;
}


