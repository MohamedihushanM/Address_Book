//This file file.c contain functiom definition of save and load contacts

#include <stdio.h>
#include "file.h"

//Function definition for savecontacts to file
void saveContactsToFile(AddressBook *addressBook) 
{
    //File open using write mode
    FILE *fp;
    fp = fopen("contact.txt","w");
    //Check file is exist or not
    if(fp == NULL)
    {
        printf("File is not founded");
        return;
    }
    //Save each contact to contact.txt file
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // 3. Write each contact's data to the file
        // We use a comma-separated format (CSV style) for easy reading later
        fprintf(fp, "%s,%s,%s\n", 
                addressBook->contacts[i].name, 
                addressBook->contacts[i].phone, 
                addressBook->contacts[i].email);
    }

    // 4. Close the file to ensure data is physically written to disk
    fclose(fp);
    
    printf("Successfully saved %d contacts to 'contacts.txt'.\n", addressBook->contactCount);
}

int loadContactsFromFile(AddressBook *addressBook) 
{
    //open contact.txt file using read mode
    FILE *fp;
    fp = fopen("contact.txt","r");

    //Check file if opened or not 
    if(fp == NULL)
    {
        return -1;
    }
    addressBook->contactCount = 0;

    // Read the file line by line
    // The format specifier %[^,] reads everything until a comma is hit
    while (addressBook->contactCount < MAX_CONTACTS && 
           fscanf(fp, " %[^,],%[^,],%[^\n]\n", 
                  addressBook->contacts[addressBook->contactCount].name, 
                  addressBook->contacts[addressBook->contactCount].phone, 
                  addressBook->contacts[addressBook->contactCount].email) == 3) 
    {
        addressBook->contactCount++;
    }
     
    //if no contacts found in file then return 1;
    if(addressBook->contactCount == 0)
    {
        return 1;
    }
    //Close the file
    fclose(fp);
    return 0;
}
