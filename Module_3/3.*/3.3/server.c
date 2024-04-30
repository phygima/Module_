#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAX_MSG_SIZE 256
#define SERVER_MSG_TYPE 1

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    int msgid;
    key_t key;
    struct msg_buffer msg;

    key = ftok("server", 52);

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Server started...\n");

    while (1) {

        if (msgrcv(msgid, &msg, sizeof(msg), SERVER_MSG_TYPE, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        pid_t client_pid = getpid();

        char client_id[20];
        snprintf(client_id, sizeof(client_id), " (from client %d)", client_pid);
        strcat(msg.msg_text, client_id);

        if (msgsnd(msgid, &msg, sizeof(msg), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        if (strcmp(msg.msg_text, "255") == 0) {
            printf("Server shutting down...\n");
            break;
        }
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
