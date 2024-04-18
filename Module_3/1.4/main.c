#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void print_prompt() {
    printf(">> ");
    fflush(stdout);
}

int main() {
    //VAR 1
    
     while (1) {
        print_prompt();

        char command[MAX_COMMAND_LEN];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        char *args[MAX_ARGS];
        char *token = strtok(command, " ");
        int arg_count = 0;
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; 

        // Запуск программы
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process terminated by signal %d\n", WTERMSIG(status));
            }
        }
    }


    //VAR 2
    // char command[100];
    
    // while (1) {
    //     printf("Enter command and args (or 'exit'): ");
    //     fgets(command, sizeof(command), stdin);
        
    //     command[strcspn(command, "\n")] = 0;
        
    //     if (strcmp(command, "exit") == 0) {
    //         break;
    //     }
        
    //     pid_t pid = fork();
        
    //     if (pid == 0) {
    //         execlp("/bin/sh", "sh", "-c", command, NULL);
    //         exit(1);
    //     } else {
    //         wait(NULL);
    //     }
    // }
    
    return 0;
}