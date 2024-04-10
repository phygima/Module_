#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "ipv4_funcs.h"


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <gateway_ip> <subnet_mask> <num_packets>\n", argv[0]);
        return 1;
    }

    uint32_t gateway_addr = ipv4_to_int(argv[1]);
    uint32_t subnet_mask = ipv4_to_int(argv[2]);
    int num_packets = atoi(argv[3]);

    srand(time(NULL));

    int same_subnet_count = 0;
    int other_subnet_count = 0;

    for (int i = 0; i < num_packets; i++) {
        uint32_t dest_ip_addr = generate_random_ip(gateway_addr, subnet_mask);

        if (is_same_subnet(dest_ip_addr, gateway_addr, subnet_mask)) {
            same_subnet_count++;
        } else {
            other_subnet_count++;
        }
    }

    printf("Same Subnet Packets: %d (%.2f%%)\n", same_subnet_count, (float)same_subnet_count / num_packets * 100);
    printf("Other Subnet Packets: %d (%.2f%%)\n", other_subnet_count, (float)other_subnet_count / num_packets * 100);

    return 0;
}
