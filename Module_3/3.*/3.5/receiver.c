#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define QUEUE_A_TO_B "/queue_a_to_b"
#define QUEUE_B_TO_A "/queue_b_to_a"
#define MAX_MSG_SIZE 256

int main() {
    mqd_t mq_a_to_b, mq_b_to_a;
    struct mq_attr attr;
    char msg[MAX_MSG_SIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    mq_a_to_b = mq_open(QUEUE_A_TO_B, O_RDONLY);
    if (mq_a_to_b == (mqd_t)-1) {
        perror("mq_open A to B");
        return 1;
    }

    mq_b_to_a = mq_open(QUEUE_B_TO_A, O_WRONLY | O_CREAT, 0666, &attr);
    if (mq_b_to_a == (mqd_t)-1) {
        perror("mq_open B to A");
        return 1;
    }

    printf("Chat started:\n");

    while (1) {
        if (mq_receive(mq_a_to_b, msg, MAX_MSG_SIZE, NULL) == -1) {
            perror("mq_receive A to B");
            return 1;
        }
        printf("Received from A: %s\n", msg);

        printf("You (B): ");
        fgets(msg, MAX_MSG_SIZE, stdin);
        msg[strcspn(msg, "\n")] = '\0';

        mq_send(mq_b_to_a, msg, strlen(msg) + 1, 0);
    }

    mq_close(mq_a_to_b);
    mq_close(mq_b_to_a);

    return 0;
}
