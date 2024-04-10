#include "ipv4_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


uint32_t ipv4_to_int(char *ipv4_addr) {
    uint32_t num = 0;
    int octet;
    char *token = strtok(ipv4_addr, ".");
    while (token != NULL) {
        octet = atoi(token);
        num = (num << 8) + octet;
        token = strtok(NULL, ".");
    }
    return num;
}

int is_same_subnet(uint32_t ip_addr, uint32_t gateway_addr, uint32_t subnet_mask) {
    return ((ip_addr & subnet_mask) == (gateway_addr & subnet_mask));
}

uint32_t generate_random_ip(uint32_t gateway_addr, uint32_t subnet_mask) {
    uint32_t random_ip = (rand() & ~subnet_mask) | (gateway_addr & subnet_mask);
    return random_ip;
}