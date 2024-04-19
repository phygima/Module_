#ifndef CONTACT_INFO_H
#define CONTACT_INFO_H

#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_SOCIAL_LENGTH 50

typedef struct {
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char social[MAX_SOCIAL_LENGTH];
} ContactInfo;

void set_phone(ContactInfo *contact_info, const char *phone);
void set_email(ContactInfo *contact_info, const char *email);
void set_social(ContactInfo *contact_info, const char *social);
char* get_phone(const ContactInfo *contact_info);
char* get_email(const ContactInfo *contact_info);
char* get_social(const ContactInfo *contact_info);

#endif
