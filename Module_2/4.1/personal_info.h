#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

#define MAX_NAME_LENGTH 50

typedef struct {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char work_place[MAX_NAME_LENGTH];
    char position[MAX_NAME_LENGTH];
} PersonalInfo;

void set_first_name(PersonalInfo *personal_info, const char *first_name);
void set_last_name(PersonalInfo *personal_info, const char *last_name);
void set_work_place(PersonalInfo *personal_info, const char *work_place);
void set_position(PersonalInfo *personal_info, const char *position);
char* get_first_name(const PersonalInfo *personal_info);
char* get_last_name(const PersonalInfo *personal_info);
char* get_work_place(const PersonalInfo *personal_info);
char* get_position(const PersonalInfo *personal_info);

#endif
