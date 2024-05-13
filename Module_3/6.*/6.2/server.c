#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_PACKET_SIZE 2048

struct udpheader {
    unsigned short int uh_sport;
    unsigned short int uh_dport;
    unsigned short int uh_len;
    unsigned short int uh_sum;
};

void process_packet(unsigned char* buffer, int size) {
    struct iphdr *iph = (struct iphdr*)buffer;
    struct udphdr *udph = (struct udphdr*)(buffer + sizeof(struct iphdr));
    unsigned char *data = buffer + sizeof(struct iphdr) + sizeof(struct udphdr);
    
    printf("Source IP: %s\n", inet_ntoa(*(struct in_addr*)&iph->saddr));
    printf("Source Port: %d\n", ntohs(udph->source));
    printf("Destination IP: %s\n", inet_ntoa(*(struct in_addr*)&iph->daddr));
    printf("Destination Port: %d\n", ntohs(udph->dest));
    printf("Data: %s\n", data);
    printf("---------------------------------------\n");
}

int main() {
    int sockfd;
    unsigned char buffer[MAX_PACKET_SIZE];
    struct sockaddr_in addr;
    int addr_len = sizeof(addr);
    int data_size;

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
 
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        data_size = recvfrom(sockfd, buffer, MAX_PACKET_SIZE, 0, (struct sockaddr *)&addr, (socklen_t*)&addr_len);
        if (data_size < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        process_packet(buffer, data_size);
    }
    
    close(sockfd);
    
    return 0;
}
