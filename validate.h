//This file validate.h contain prototype of validation functions

#ifndef VALIDATE_H
#define VALIDATE_H
#include "contact.h"

int validate_name(char name[]);
int validate_phone(AddressBook *addressBook,char phone[]);
int validate_email(AddressBook *addressBook,char email[]);

#endif