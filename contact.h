#ifndef CONTACT_H
#define CONTACT_H

//Define maximum contacts 100
#define MAX_CONTACTS 100

 // Declare  contact structure contain name,phone and email
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

//Declare AddressBook structure contain structure contacts and contactscount
typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;


//Prototypes of function We used on addressbook
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);


#endif
