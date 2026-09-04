//Validate.c file contain function definition of Validation function 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validate.h"
#include "contact.h"

//Function definition for validate name
int validate_name(char name[]) 
{
    // Check if name is empty
    if (strlen(name) == 0) 
    return 0;

    for (int i = 0; name[i] != '\0'; i++) 
    {
        // If any character is NOT a letter or space it's invalid
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            return 0; 
        }
    }
    return 1; // All characters passed
}

//Function definition for validate phone number
int validate_phone(AddressBook *addressBook,char phone[]) 
{
    // check phone has exactly 10 characters
    if (strlen(phone) != 10)
    {
        printf("Phone must be 10 digits\n");
        return 0;

    } 

    for (int i = 0; i < 10; i++) 
    {
        // If any character is not a digit, it's invalid
        if (!isdigit(phone[i])) 
        {
            printf("Phone number must be digits\n");
            return 0;
        }
    }
    
    //Check Phone number is already existed if yes then return 0
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone,phone) == 0)
        {
            printf("Phone number already exist\n");
            return 0;
        }

    }
    return 1;// All characters passed
}

//Function definition for validate email 
int validate_email(AddressBook *addressBook,char email[]) 
{
    int len = strlen(email);
    // check Email must be long enough to contain "@gmail.com"
    if (len <= 10)
    {
        printf("Email must have @gmail.com\n");
        return 0;
    } 

    // strcmp returns 0 ,if strings match. 
    // We check the end of the string starting from (length - 10)
    if (strcmp(email + len - 10, "@gmail.com") == 0) 
    {
        return 1;
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        //check email already exist or not
        if (strcmp(addressBook->contacts[i].email,email) == 0)
        {
            printf("Email already exist\n");
            return 0;
        }

    }
    printf("Email must have @gmail.com\n");
    return 0;

}