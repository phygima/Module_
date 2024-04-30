#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME "/server_queue"
#define MAX_MSG_SIZE 256
#define EXIT_MSG_PRIORITY 255

int main(){
    mqd_t server_queue, client_queue;
    char client_queue_name[64];
    char msg[MAX_MSG_SIZE];

    sprintf(client_queue_name, "/client_queue_%d", getpid());

    client_queue = mq_open(client_queue_name,  O_RDWR | O_CREAT, 0666, NULL);
     if (client_queue == (mqd_t)-1) {
        perror("mq_open client");
        exit(1);
    }
    server_queue = mq_open(SERVER_QUEUE_NAME, O_WRONLY);
    if (server_queue == (mqd_t)-1) {
        perror("mq_open server");
        exit(1);
    }

    printf("Connected to the server.\n");

    while (1)
    {
        printf("You: ");
        fgets(msg, MAX_MSG_SIZE, stdin);
        msg[strcspn(msg, "\n")] = '\0';

        if (strcmp(msg, "exit") == 0) {
            if (mq_send(server_queue, msg, strlen(msg) + 1, EXIT_MSG_PRIORITY) == -1) {
                perror("mq_send exit client");
                continue;
            }
            break;
        }

        char formatted_msg[MAX_MSG_SIZE];
        sprintf(formatted_msg, "%d:%s", getpid(), msg);

        if (mq_send(server_queue, formatted_msg, strlen(msg) + 1, 0) == -1) {
            perror("mq_send client");
            continue;
        }

        if (mq_receive(client_queue, msg, MAX_MSG_SIZE, NULL) == -1) {
            perror("mq_receive client");
            continue;
        }

        printf("Received: %s\n", msg);
    }
    
    mq_close(client_queue);
    mq_unlink(client_queue_name);

    return 0;

}