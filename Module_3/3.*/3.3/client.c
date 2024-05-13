#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Enter 'exit' to quit.\n");

    while (1) {
        printf("Enter message: ");
        fgets(msg.msg_text, MAX_MSG_SIZE, stdin);

        msg.msg_text[strlen(msg.msg_text) - 1] = '\0';

        msg.msg_type = SERVER_MSG_TYPE;
        if (msgsnd(msgid, &msg, sizeof(msg), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        if (strcmp(msg.msg_text, "exit") == 0) {
            msg.msg_type = SERVER_MSG_TYPE;
            strcpy(msg.msg_text, "255");
            if (msgsnd(msgid, &msg, sizeof(msg), 0) == -1) {
                perror("msgsnd");
                exit(1);
            }
            break;
        }
    }

    return 0;
}
