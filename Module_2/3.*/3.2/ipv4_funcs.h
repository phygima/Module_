#ifndef IPV4_FUNCS_H
#define IPV4_FUNCS_H

#define IPV4_ADDR_LEN 32

uint32_t ipv4_to_int(char *ipv4_addr);
int is_same_subnet(uint32_t ip_addr, uint32_t gateway_addr, uint32_t subnet_mask);
uint32_t generate_random_ip(uint32_t gateway_addr, uint32_t subnet_mask);

#endif