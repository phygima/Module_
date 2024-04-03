#ifndef ALL_PERMISSONS_H
#define ALL_PERMISSIONS_H

#include <sys/stat.h>


void display_permissions(mode_t mode);

void bit_permissions(mode_t mode);

mode_t letter_permissions(const char* permission_str);

mode_t let_format(const char* permission_str);

#endif