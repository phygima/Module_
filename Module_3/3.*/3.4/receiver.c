#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_queue"
#define MAX_MSG_SIZE 256
#define MSG_STOP 255

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char msg[MAX_MSG_SIZE];
    unsigned int prio;

    mq_getattr(mq, &attr);

    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
   
    while(1){
        
        if(mq_receive(mq, msg, MAX_MSG_SIZE, &prio) == -1){
            perror("mq_receive");
            return 1;
        }

        if(prio == MSG_STOP){
            break;
        }

        printf("Received msg: %s\n", msg);
    }

    mq_close(mq);

    return 0;
    
}

