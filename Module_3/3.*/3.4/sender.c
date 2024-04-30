#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_queue"
#define MAX_MSG_SIZE 256

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char msg[MAX_MSG_SIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_WRONLY | O_CREAT, 0644, &attr );

    
   
    while(1){
        printf("Enter your msg ('exit' to quit): ");
        fgets(msg,MAX_MSG_SIZE,stdin);
        msg[strcspn(msg,"\n")] = '\0';

        if(strcmp(msg, "exit") == 0){
            break;
        }

        mq_send(mq, msg, strlen(msg) + 1, 1);
    }

    mq_send(mq, "", 0, 255);
    mq_close(mq);

    return 0;
    
}

