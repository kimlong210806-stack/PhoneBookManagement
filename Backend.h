#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include <vector>

using namespace std;

struct Contact {
    string id;
    string owner;
    string name;
    string phone;
    string email;
    string address;
    string note;
};


// View 
void viewContactsFile(const string& currentUser);
void viewContactDetails(const string& currentUser);
void viewContactsSorted(const string& currentUser);

// Search 
void searchContacts(const string& currentUser);

// Add, Update, Delete 
void addContact(const string& currentUser);
void updateContact(const string& currentUser);
void deleteContact(const string& currentUser);
void deleteMultipleContacts(const string& currentUser);

// Helper functions
bool isPhoneExists(const string& phone, const string& currentUser);
int countUserContacts(const string& currentUser);
vector<Contact> loadUserContacts(const string& currentUser);
void sortContactsByName(vector<Contact>& contacts);

#endif
