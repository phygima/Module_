#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080
#define MAX_MSG_SIZE 1024
#define MAX_CLIENTS 2

typedef struct {
    int sockfd;
    struct sockaddr_in cliaddr;
} ClientInfo;

void *relay_messages(void *args) {
    ClientInfo **clients = (ClientInfo **)args;
    char buffer[MAX_MSG_SIZE];
    int n;
    socklen_t len;
    
    while (1) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            len = sizeof(clients[i]->cliaddr);
            n = recvfrom(clients[i]->sockfd, (char *)buffer, MAX_MSG_SIZE, MSG_WAITALL, (struct sockaddr *)&clients[i]->cliaddr, &len);
            buffer[n] = '\0';

            int other_client_index = (i + 1) % MAX_CLIENTS;
            sendto(clients[other_client_index]->sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&clients[other_client_index]->cliaddr, len);
        }
    }
    
    pthread_exit(NULL);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    pthread_t tid;
    ClientInfo *clients[MAX_CLIENTS];
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = (ClientInfo *)malloc(sizeof(ClientInfo));
        clients[i]->sockfd = sockfd;
        socklen_t len = sizeof(clients[i]->cliaddr);
        if (recvfrom(sockfd, NULL, 0, MSG_PEEK, (struct sockaddr *)&clients[i]->cliaddr, &len) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }
    }
    
    if (pthread_create(&tid, NULL, relay_messages, (void *)clients) != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(tid, NULL);
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        close(clients[i]->sockfd);
        free(clients[i]);
    }
    
    close(sockfd);
    
    return 0;
}
