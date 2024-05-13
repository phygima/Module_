#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen, n;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    fd_set readfds;
    int max_sd, sd;
    int client_sockets[MAX_CLIENTS] = {0};
    int activity, i;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    
    listen(sockfd, MAX_CLIENTS);
    
    clilen = sizeof(cli_addr);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;

        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) ) 
            printf("select error");
        
        if (FD_ISSET(sockfd, &readfds)) {
            newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
            if (newsockfd < 0)
                error("ERROR on accept");
            
            printf("New connection, socket fd is %d, ip is : %s, port : %d\n", newsockfd, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = newsockfd;
                    break;
                }
            }
        }
        
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (FD_ISSET(sd, &readfds)) {
                if ((n = read(sd, buffer, BUFFER_SIZE)) == 0) {
                    getpeername(sd, (struct sockaddr*)&cli_addr, (socklen_t*)&clilen);
                    printf("Host disconnected, ip %s, port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
                    close(sd);
                    client_sockets[i] = 0;
                } else {
                    buffer[n] = '\0';
                    printf("Received from client: %s", buffer);
                    write(sd, buffer, strlen(buffer));
                }
            }
        }
    }

    return 0;
}
