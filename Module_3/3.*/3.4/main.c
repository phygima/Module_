#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_queue"
#define MAX_MSG_SIZE 256

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_MSG_SIZE + 1];

    // Установка атрибутов очереди сообщений
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Создание очереди сообщений (если еще не создана)
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Chat started.\n");

    while (1) {
        // Чтение сообщения из очереди
        if (mq_receive(mq, buffer, MAX_MSG_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(1);
        }
        buffer[MAX_MSG_SIZE] = '\0'; // Убедиться, что строка заканчивается нулевым символом
        printf("Received: %s\n", buffer);

        // Ввод сообщения для отправки
        printf("Enter message to send (max %d characters): ", MAX_MSG_SIZE);
        fgets(buffer, MAX_MSG_SIZE, stdin);
        // Удаление символа новой строки, добавленного fgets
        buffer[strcspn(buffer, "\n")] = '\0';

        // Отправка сообщения в очередь
        if (mq_send(mq, buffer, strlen(buffer), 0) == -1) {
            perror("mq_send");
            exit(1);
        }
    }

    // Закрытие очереди сообщений
    if (mq_close(mq) == -1) {
        perror("mq_close");
        exit(1);
    }

    return 0;
}
