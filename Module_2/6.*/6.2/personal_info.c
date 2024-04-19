#include <string.h>
#include "personal_info.h"

void set_first_name(PersonalInfo *personal_info, const char *first_name) {
    strncpy(personal_info->first_name, first_name, MAX_NAME_LENGTH);
    personal_info->first_name[MAX_NAME_LENGTH - 1] = '\0';
}

void set_last_name(PersonalInfo *personal_info, const char *last_name) {
    strncpy(personal_info->last_name, last_name, MAX_NAME_LENGTH);
    personal_info->last_name[MAX_NAME_LENGTH - 1] = '\0';
}

void set_work_place(PersonalInfo *personal_info, const char *work_place) {
    strncpy(personal_info->work_place, work_place, MAX_NAME_LENGTH);
    personal_info->work_place[MAX_NAME_LENGTH - 1] = '\0';
}

void set_position(PersonalInfo *personal_info, const char *position) {
    strncpy(personal_info->position, position, MAX_NAME_LENGTH);
    personal_info->position[MAX_NAME_LENGTH - 1] = '\0';
}

char* get_first_name(const PersonalInfo *personal_info) {
    return personal_info->first_name;
}

char* get_last_name(const PersonalInfo *personal_info) {
    return personal_info->last_name;
}

char* get_work_place(const PersonalInfo *personal_info) {
    return personal_info->work_place;
}

char* get_position(const PersonalInfo *personal_info) {
    return personal_info->position;
}
