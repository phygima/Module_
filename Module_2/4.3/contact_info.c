#include <string.h>
#include "contact_info.h"

void set_phone(ContactInfo *contact_info, const char *phone) {
    strncpy(contact_info->phone, phone, MAX_PHONE_LENGTH);
    contact_info->phone[MAX_PHONE_LENGTH - 1] = '\0';
}

void set_email(ContactInfo *contact_info, const char *email) {
    strncpy(contact_info->email, email, MAX_EMAIL_LENGTH);
    contact_info->email[MAX_EMAIL_LENGTH - 1] = '\0';
}

void set_social(ContactInfo *contact_info, const char *social) {
    strncpy(contact_info->social, social, MAX_SOCIAL_LENGTH);
    contact_info->social[MAX_SOCIAL_LENGTH - 1] = '\0';
}

char* get_phone(const ContactInfo *contact_info) {
    return contact_info->phone;
}

char* get_email(const ContactInfo *contact_info) {
    return contact_info->email;
}

char* get_social(const ContactInfo *contact_info) {
    return contact_info->social;
}
