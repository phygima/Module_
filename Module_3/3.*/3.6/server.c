#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME "/server_queue"
#define MAX_CLIENTS 10
#define MAX_MSG_SIZE 1024
#define EXIT_MSG_PRIORITY 255

typedef struct {
    mqd_t client_queue;
    int client_id;
} ClientInfo;

ClientInfo clients[MAX_CLIENTS];
int num_clients = 0;

int findClientIndexByQueue(mqd_t client_queue) {
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].client_queue == client_queue) {
            return i;
        }
    }
    return -1;
}

int main() {
    mqd_t server_queue;
    struct mq_attr attr;
    char msg[MAX_MSG_SIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    server_queue = mq_open(SERVER_QUEUE_NAME, O_RDWR | O_CREAT, 0644, &attr);
    if (server_queue == (mqd_t)-1) {
        perror("mq_open server");
        exit(1);
    }

    printf("Server started.\n");

    while (1) {
        if (mq_receive(server_queue, msg, MAX_MSG_SIZE, NULL) == -1) {
            perror("mq_receive server");
            continue;
        }

        char *client_id_str = strtok(msg, ":");
        if (client_id_str == NULL) {
            printf("Invalid message format: %s\n", msg);
            continue;
        }
        int client_id = atoi(client_id_str);

        if (client_id == EXIT_MSG_PRIORITY) {
            printf("Received exit message from client.\n");
            break;
        }

        int client_index = findClientIndexByQueue(clients[client_id].client_queue);
        if (client_index == -1) {
            printf("New client connected: %d\n", client_id);
            clients[num_clients].client_queue = mq_open(msg, O_WRONLY);
            clients[num_clients].client_id = client_id;
            num_clients++;
        } else {
            printf("Received message from client %d: %s\n", client_id, msg);

            char new_msg[MAX_MSG_SIZE];
            sprintf(new_msg, "Client %d: %s", client_id, strtok(NULL, ""));

            for (int i = 0; i < num_clients; i++) {
                if (mq_send(clients[i].client_queue, new_msg, strlen(new_msg) + 1, 0) == -1) {
                    perror("mq_send server");
                    continue;
                }
            }
        }
    }

    mq_close(server_queue);
    mq_unlink(SERVER_QUEUE_NAME);

    return 0;
}
