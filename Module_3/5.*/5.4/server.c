#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFSIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    FILE *file;
    char buffer[BUFSIZE];
    ssize_t bytes_received;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    if (listen(sockfd, 5) < 0) {
        error("ERROR on listening");
    }

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    file = fopen("received_file.txt", "wb");
    if (!file) {
        error("Error opening file");
    }

    while ((bytes_received = recv(newsockfd, buffer, BUFSIZE, 0)) > 0) {
        if (fwrite(buffer, 1, bytes_received, file) < bytes_received) {
            error("Error writing to file");
        }
    }

    if (bytes_received < 0) {
        error("Error receiving file");
    }

    fclose(file);
    close(newsockfd);
    close(sockfd);

    printf("File received successfully\n");

    return 0;
}
