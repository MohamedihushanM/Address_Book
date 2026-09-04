//This Contain.c contains functions Definition initialize,create,Edit,delete,save,exit and search cantacts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validate.h"

//Function definition for list all contact
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    printf("---------------------------------------------------------------------------\n");
    printf("                    ENTER INTO LIST CONTACT");
    printf("\n---------------------------------------------------------------------------\n");

    // Sort contacts based on the chosen criteria
    // Check if the address book is empty
    if (addressBook->contactCount == 0) {
        printf("\n==========================================\n");
        printf("       Address Book is currently empty.   \n");
        printf("==========================================\n");
        return;
    }

    // Sort contacts based on criteria
    if (sortCriteria == 1) 
    {
        for (int i = 0; i < addressBook->contactCount - 1; i++) 
        {
            for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
            {
                // Compare names alphabetically
                if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) 
                {
                    // Swap the contact structures
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
    }

    //Print the Header
    printf("\n---------------------------------------------------------------------------\n");
    printf("%-20s %-15s %-25s\n", "| Name", "| Phonenumber", "| Email");
    printf("---------------------------------------------------------------------------\n");

    //Iterate through the array and print details
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%s%-20s %-15s %-25s\n","| ",  
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);
    }
    printf("---------------------------------------------------------------------------\n");
    printf("Total Contacts: %d\n", addressBook->contactCount);
}

//initialize contacts from contact.txt or dummy contact from populate function
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;

    //Functiom call for loadcontactsfromfile
    int loadstatus = loadContactsFromFile(addressBook);

    //if function return 0 then Successfully loaded from file
    if (loadstatus == 0) 
    {
        printf("Contacts loaded successfully from file\n");
    }
    //not then using dummy contacts from poplate function
    else
    {
        printf("No storage file found. Populating default data...\n");
        //Populate function call
        populateAddressBook(addressBook);
    }
}

//Function which save changes we made in addressbook
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    printf("\n----------------------------------------\n");
    printf("               Changes saved              \n");
    printf("----------------------------------------\n");
    exit(EXIT_SUCCESS); // Exit the program
}

//Function definition for create new contact
void createContact(AddressBook *addressBook)
{
    printf("---------------------------------------------------------------------------\n");
    printf("                    ENTER INTO CREATE CONTACT");
    printf("\n---------------------------------------------------------------------------\n");
	/* Define the logic to create a Contacts */
    //check addressBook full or not
    if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        //if full then execute below statement
        printf("Error: Address Book Full!\n");
        return;
    }

    Contact newContact;
    
    //Read name from user
    printf("Enter Name: ");
    scanf(" %[^\n]", newContact.name);
    //Validate name
    if(!validate_name(newContact.name))
    {
        //if not valid name
        printf(("Name must be alphabets\n"));
        return;
    }

    //Read phone no. from user
    printf("Enter Phone: ");
    scanf("%s", newContact.phone);
    //Validate phone no.
    if(!validate_phone(&*addressBook,newContact.phone)) 
    {
        //if not valid phone no.
        return;
    }

    //Read email from user
    printf("Enter Email: ");
    scanf("%s", newContact.email);
    //Validate email
    if (!validate_email(&*addressBook,newContact.email)) 
    {
        //if not valid email
        return;
    }

    //check email already exist

    //After validate all input and increament contactcount and new contact will added to addressbook 
    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Contact added!\n");
}


void searchContact(AddressBook *addressBook) 
{
    printf("---------------------------------------------------------------------------\n");
    printf("                    ENTER INTO SEARCH CONTACT");
    printf("\n---------------------------------------------------------------------------\n");
    //Check if address book is empty
    if (addressBook->contactCount == 0) 
    {
        printf("Address book is empty. Nothing to search.\n");
        return;
    }

    int choice;
    char name[50];
    char phone[50];
    char email[50];
    int found = 0;

    //Read choice from user
    printf("Search Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clean newline from buffer

    //Read input from user based on choice
    switch (choice)
    {
        case 1:
            printf("Enter the name you want to search: ");
            scanf(" %[^\n]", name);
            break;
        case 2:
            printf("Enter the phone number you want to search: ");
            scanf(" %[^\n]", phone);
            break;
        case 3:
            printf("Enter the email you want to search: ");
            scanf(" %[^\n]", email);
            break;
        default:
            printf("Invalid Choice\n");
            return;
             
    }
    printf("------------------------------------------------------------\n");

    //Loop run for contactcount to search whether contact exist or not
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;

        switch (choice) 
        {
            case 1:
                if (strcmp(addressBook->contacts[i].name, name) == 0) 
                {
                   match = 1;
                   break;
                }
            case 2:
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    match = 1;
                    break;
                }
            case 3:
                if (strcmp(addressBook->contacts[i].email, email) == 0) 
                {
                    match = 1;
                    break;
                }
        }

        //If contact present then it will print
        if (match) 
        {
            printf("%-20s %-15s %-25s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found++;
        }
    }

    //if not founded then it will print not founded
    if (found == 0) 
    {
        printf("No contacts found matching\n");
    }

    printf("------------------------------------------------------------\n");
 

}

//Function for edit contacts
void editContact(AddressBook *addressBook)
{
    printf("---------------------------------------------------------------------------\n");
    printf("                    ENTER INTO EDIT CONTACT");
    printf("\n---------------------------------------------------------------------------\n");

    //if contactcount is 0 then addressbook is empty
    if (addressBook->contactCount == 0) 
    {
        printf("Address book is empty. Nothing to edit.\n");
        return;
    }


    int choice;
    char name[50];
    char phone[50];
    char email[50];
    int found = 0;
    int foundIndex = 0;

    //Read choice from user
    printf("Search Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clean newline from buffer

    //Read input from user based on choice
    switch (choice)
    {
        case 1:
            printf("Enter the name you want to search: ");
            scanf(" %[^\n]", name);
            break;
        case 2:
            printf("Enter the phone number you want to search: ");
            scanf(" %[^\n]", phone);
            break;
        case 3:
            printf("Enter the email you want to search: ");
            scanf(" %[^\n]", email);
            break;
        default:
            printf("Invalid Choice\n");
            return;
             
    }
    printf("------------------------------------------------------------\n");

    //Loop run for contactcount to search whether contact present or not
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;

        switch (choice) 
        {
            case 1:
                if (strcmp(addressBook->contacts[i].name, name) == 0) 
                {
                   match = 1;
                   foundIndex = i;
                   break;
                }
            case 2:
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    match = 1;
                    foundIndex = i;
                    break;
                }
            case 3:
                if (strcmp(addressBook->contacts[i].email, email) == 0) 
                {
                    match = 1;
                    foundIndex = i;
                    break;
                }
        }

        //If contact present then it will print
        if (match) 
        {
            printf("%-20s %-15s %-25s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found++;
        }
    }

    //if not founded then it will print not founded
    if (found == 0) 
    {
        printf("No contacts found matching to edit\n");
    }

    printf("------------------------------------------------------------\n");


    //if one contact found from search then edit 
    if(found == 1)
    { 
        choice = 0;
       // 2. Provide Edit Menu
       printf("\nContact Found. What would you like to edit?\n");
       printf("1. Edit Name\n");
       printf("2. Edit Phone\n");
       printf("3. Edit Email\n");
       printf("Enter your choice: ");
       scanf("%d", &choice);
       getchar(); // Clear newline

       //Validate what we edit
       switch (choice) 
       {
            case 1:
                printf("Enter new Name: ");
                scanf(" %[^\n]", name);
                if(!validate_name(name)) 
                {
                    printf("Name must be alphabets\n");
                   return;
                }
                else
                {
                       strcpy(addressBook->contacts[foundIndex].name,name);
                }
                break;
            case 2:
                printf("Enter new Phone: ");
                scanf("%s", phone);
                if(!validate_phone(&*addressBook,phone)) 
                {
                   return;
                }
                else
                {
                       strcpy(addressBook->contacts[foundIndex].phone,phone);
                }  
                break;
            case 3:
                printf("Enter new Email: ");
                scanf("%s", email);
                if(!validate_email(&*addressBook,email)) 
                {
                    return;
                }
                else
                {
                       strcpy(addressBook->contacts[foundIndex].email,email);
                }
                break;
            default:
                printf("Invalid choice.\n");
                return;
        }

        printf("Contact updated successfully!\n");
    }

    //if more than one contact founded when search 
    else if(found > 1)
    {
        //Read choice from user phoneno. or email
        choice = 0;
        int flag = 0;
        printf("More than one contact Appeared\n");
        printf("Search Contact By:\n");
        printf("1. Phone Number\n");
        printf("2. Email ID\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        //based on choice store 
        switch (choice)
        {
            case 1:
                printf("Enter the phone number you want to search: ");
                scanf(" %[^\n]", phone);
                break;
            case 2:
                printf("Enter the email you want to search: ");
                scanf(" %[^\n]", email);
                break;
            default:
                printf("Invalid Choice\n");
                return;
             
        }
        printf("------------------------------------------------------------\n");

        //search input is exist or not
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            int match = 0;

            switch (choice) 
            {
                case 1:
                    if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                       match = 1;
                       foundIndex = i;
                       break;
                    }
                case 2:
                    if (strcmp(addressBook->contacts[i].email, email) == 0) 
                    {
                        match = 1;
                        foundIndex = i;
                        break;
                    }
            }

            //If contact present then it will print
            if (match) 
            {
                printf("%-20s %-15s %-25s\n", 
                    addressBook->contacts[i].name, 
                    addressBook->contacts[i].phone, 
                    addressBook->contacts[i].email);
                flag++;
            }
        }
        //if no contact founded then
        if(flag  == 0)
        {
            printf("No matching contact found to edit.\n");
        }
        printf("------------------------------------------------------------\n");

        //if one contact founded
        if(flag == 1)
        { 
           // 2. Provide Edit Menu
           choice = 0;
           printf("\nContact Found. What would you like to edit?\n");
           printf("1. Edit Name\n");
           printf("2. Edit Phone\n");
           printf("3. Edit Email\n");
           printf("Enter your choice: ");
           scanf("%d", &choice);
           getchar(); // Clear newline

           //Based on choice validate and edit
           switch (choice) 
           {
            
                case 1:
                    printf("Enter new Name: ");
                    scanf(" %[^\n]", name);
                    if(!validate_name(name)) 
                    {
                        printf("Name must be alphabets\n");
                        return;
                    }
                    else
                    {
                       strcpy(addressBook->contacts[foundIndex].name,name);
                    }
                    break;
                case 2:
                    printf("Enter new Phone: ");
                    scanf("%s", phone);
                    if(!validate_phone(&*addressBook,phone)) 
                    {
                       return;
                    }
                    else
                    {
                       strcpy(addressBook->contacts[foundIndex].phone,phone);
                    }  
                    break;
                case 3:
                    printf("Enter new Email: ");
                    scanf("%s", email);
                    if (!validate_email(&*addressBook,email)) 
                    {
                        return;
                    }
                    else
                    {
                       strcpy(addressBook->contacts[foundIndex].email,email);
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }

            printf("Contact updated successfully!\n");
        }
    }
}

//Function for delete contact
void deleteContact(AddressBook *addressBook)
{
    printf("---------------------------------------------------------------------------\n");
    printf("                    ENTER INTO DELETE CONTACT");
    printf("\n---------------------------------------------------------------------------\n");

    //if contact is empty
    if (addressBook->contactCount == 0) 
    {
        printf("Address book is empty. Nothing to edit.\n");
        return;
    }

    //Read input from user
    int choice;
    char name[50];
    char phone[50];
    char email[50];
    int found = 0;
    int foundIndex = 0;

    //Read choice from user
    printf("Search Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clean newline from buffer

    //Read input from user based on choice
    switch (choice)
    {
        case 1:
            printf("Enter the name you want to search: ");
            scanf(" %[^\n]", name);
            break;
        case 2:
            printf("Enter the phone number you want to search: ");
            scanf(" %[^\n]", phone);
            break;
        case 3:
            printf("Enter the email you want to search: ");
            scanf(" %[^\n]", email);
            break;
        default:
            printf("Invalid Choice\n");
            return;
             
    }
    printf("------------------------------------------------------------\n");

    //Loop run for contactcount to search whether contact present or not
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;

        switch (choice) 
        {
            case 1:
                if (strcmp(addressBook->contacts[i].name, name) == 0) 
                {
                   match = 1;
                   foundIndex = i;
                   break;
                }
            case 2:
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    match = 1;
                    foundIndex = i;
                    break;
                }
            case 3:
                if (strcmp(addressBook->contacts[i].email, email) == 0) 
                {
                    match = 1;
                    foundIndex = i;
                    break;
                }
        }

        //If contact present then it will print
        if (match) 
        {
            printf("%-20s %-15s %-25s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found++;
        }
    }
    //if not founded
    if(found == 0) 
    {
        printf("No matching contact found to delete.\n");
    }
     printf("------------------------------------------------------------\n");

    //if one conatcat found then 
    if (found == 1) 
    {
        char confirm;
        printf("Are you sure you want to delete this contact? (y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {
            // 3. SHIFTING LOGIC
            // Move everything from foundIndex + 1 to the left by 1
            for (int j = foundIndex; j < addressBook->contactCount - 1; j++) 
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

            addressBook->contactCount--; // Decrement the total count
            printf("Contact deleted successfully.\n");
        } 
        else 
        {
            printf("Deletion cancelled.\n");
        }
    }

    //More then one contact founded
    else if(found > 1)
    {
        //Read choice from user
        choice = 0;
        int flag = 0;
        printf("More than one contact appeared\n");
        printf("Search Contact By:\n");
        printf("1. Phone Number\n");
        printf("2. Email ID\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        //Based on choice read inpurt from user
        switch (choice)
        {
            case 1:
                printf("Enter the phone number you want to search: ");
                scanf(" %[^\n]", phone);
                break;
            case 2:
                printf("Enter the email you want to search: ");
                scanf(" %[^\n]", email);
                break;
            default:
                printf("Invalid Choice\n");
                return;
             
        }
        printf("------------------------------------------------------------\n");

        //searching contacts 
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            int match = 0;

            switch (choice) 
            {
                case 1:
                    if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                       match = 1;
                       foundIndex = i;
                       break;
                    }
                case 2:
                    if (strcmp(addressBook->contacts[i].email, email) == 0) 
                    {
                        match = 1;
                        foundIndex = i;
                        break;
                    }
            }

            //If contact existed then it will print
            if (match) 
            {
                printf("%-20s %-15s %-25s\n", 
                    addressBook->contacts[i].name, 
                    addressBook->contacts[i].phone, 
                    addressBook->contacts[i].email);
                flag++;
            }
        }
        //if not exist
        if(flag  == 0)
        {
            printf("No matching contact found to delete.\n");

        }

        printf("------------------------------------------------------------\n");

        //if one contact founded
        if(flag == 1)
        {
            //confirming delete or not
            char confirm;
            printf("Are you sure you want to delete this contact? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') 
            {
            // 3. SHIFTING LOGIC
            // Move everything from foundIndex + 1 to the left by 1
                for (int j = foundIndex; j < addressBook->contactCount - 1; j++) 
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }

                addressBook->contactCount--; // Decrement the total count
                printf("Contact deleted successfully.\n");
            } 
            else 
            {
               printf("Deletion cancelled.\n");
            }
        }
        
    }   
}
