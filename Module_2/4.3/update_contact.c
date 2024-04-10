#include <stdio.h>
#include "update_contact.h"
#include "contact.h"

void update_contact_details(Contact *contact) {
    printf("Enter new contact details:\n");
    printf("Enter first name: ");
    fgets(contact->personal_info.first_name, MAX_NAME_LENGTH, stdin);
    set_first_name(&contact->personal_info, contact->personal_info.first_name);

    printf("Enter last name: ");
    fgets(contact->personal_info.last_name, MAX_NAME_LENGTH, stdin);
    set_last_name(&contact->personal_info, contact->personal_info.last_name);

    printf("Enter work place: ");
    fgets(contact->personal_info.work_place, MAX_NAME_LENGTH, stdin);
    set_work_place(&contact->personal_info, contact->personal_info.work_place);

    printf("Enter position: ");
    fgets(contact->personal_info.position, MAX_NAME_LENGTH, stdin);
    set_position(&contact->personal_info, contact->personal_info.position);

    printf("Enter phone number: ");
    fgets(contact->contact_info.phone, MAX_PHONE_LENGTH, stdin);
    set_phone(&contact->contact_info, contact->contact_info.phone);

    printf("Enter email address: ");
    fgets(contact->contact_info.email, MAX_EMAIL_LENGTH, stdin);
    set_email(&contact->contact_info, contact->contact_info.email);

    printf("Enter social media profile: ");
    fgets(contact->contact_info.social, MAX_SOCIAL_LENGTH, stdin);
    set_social(&contact->contact_info, contact->contact_info.social);
}
