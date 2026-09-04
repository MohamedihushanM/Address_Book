/*
Name: Mohamed ihushan
Date: 10/05/2026
Description: Addressbook Project 
*/
#include <stdio.h>
#include "contact.h"

//Main function of addressbook
int main() {
    int choice;
    //typedef declare Structure name as addressBook
    AddressBook addressBook;

    //Function call for initialize addressbook contacts
    initialize(&addressBook); // Initialize the address book

    //AddressBook Menu using do while loop 
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        //using switch case to call function  We want
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, choice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                //saveContactsToFile(&addressBook);
                saveAndExit(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        //Loop run until choice is not 7
    } while (choice != 7);
    
       return 0;
}
