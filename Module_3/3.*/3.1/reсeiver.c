#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 1024

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_SIZE];
};


int main() {
    key_t key;
    int msg_id;
    struct msg_buffer message;

    key = ftok("sender.c", 52);
    msg_id = msgget(key,0666 | IPC_CREAT);

    while(1){
        msgrcv(msg_id, &message, sizeof(message), 0, 0);

        if(message.msg_type == 255)
            break;

        printf("Get msg: %s", message.msg_text);
    }

    msgctl(msg_id,IPC_RMID,NULL);
    exit(0);

    return 0;

}