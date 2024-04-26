#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_SIZE 1024

struct msg_buffer{
    long msg_type;
    char msg_text[MAX_SIZE];
};

int main(){

    key_t key;
    int msg_id;
    struct msg_buffer message;

    key = ftok("sender.c", 52);
    msg_id = msgget(key, 0666 | IPC_CREAT);

    while(1) {
        printf("Enter your message (type 255 to exit): ");
        fgets(message.msg_text, MAX_SIZE, stdin);

        if (strncmp(message.msg_text, "exit", 4) == 0) {
            message.msg_type = 255;
            msgsnd(msg_id, &message, sizeof(message), 0);
            exit(EXIT_SUCCESS);
        }

        message.msg_type = 1;
        msgsnd(msg_id, &message, sizeof(message), 0);
    }

    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}