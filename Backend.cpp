#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <vector>
#include "Backend.h"

using namespace std;

const string CONTACTS_FILE = "Contacts.txt";


vector<Contact> loadUserContacts(const string& currentUser) {
    vector<Contact> contacts;
    ifstream file(CONTACTS_FILE);
    if (!file.is_open()) return contacts;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;

        getline(ss, c.id, '|');
        getline(ss, c.owner, '|');
        getline(ss, c.name, '|');
        getline(ss, c.phone, '|');
        getline(ss, c.email, '|');
        getline(ss, c.address, '|');
        getline(ss, c.note);

        if (c.owner == currentUser) {
            contacts.push_back(c);
        }
    }
    file.close();
    return contacts;
}


// Count contacts
int countUserContacts(const string& currentUser) {
    return loadUserContacts(currentUser).size();
}


// View all contacts
void viewContactsFile(const string& currentUser) {
    vector<Contact> contacts = loadUserContacts(currentUser);

    if (contacts.empty()) {
        cout << "\nKhong co danh ba nao.\n";
        return;
    }

    cout << "\n========== DANH BA CUA BAN ==========\n";
    cout << left << setw(5) << "ID"
        << setw(25) << "Ten"
        << setw(15) << "So dien thoai" << endl;
    cout << string(60, '-') << endl;

    for (const auto& c : contacts) {
        cout << left << setw(5) << c.id
            << setw(25) << c.name
            << setw(15) << c.phone;
    }
    cout << "\nTong: " << contacts.size() << " danh ba\n";
}

// View contact details
void viewContactDetails(const string& currentUser) {
    string id;
    cout << "\nNhap ID danh ba can xem: ";
    cin >> id;

    vector<Contact> contacts = loadUserContacts(currentUser);

    for (const auto& c : contacts) {
        if (c.id == id) {
            cout << "\n========== CHI TIET DANH BA ==========\n";
            cout << "ID: " << c.id << endl;
            cout << "Ten: " << c.name << endl;
            cout << "So dien thoai: " << c.phone << endl;
            cout << "Email: " << c.email << endl;
            cout << "Dia chi: " << c.address << endl;
            cout << "Ghi chu: " << c.note << endl;
            cout << "======================================\n";
            return;
        }
    }
    cout << "Khong tim thay danh ba!\n";
}

// View contacts sorted alphabetically
void viewContactsSorted(const string& currentUser) {
    vector<Contact> contacts = loadUserContacts(currentUser);

    if (contacts.empty()) {
        cout << "\nKhong co danh ba nao.\n";
        return;
    }

    sortContactsByName(contacts);

    cout << "\n========== DANH BA (SAP XEP THEO TEN) ==========\n";
    cout << left << setw(5) << "ID"
        << setw(25) << "Ten"
        << setw(15) << "So dien thoai" << endl;
    cout << string(45, '-') << endl;

    for (const auto& c : contacts) {
        cout << left << setw(5) << c.id
            << setw(25) << c.name
            << setw(15) << c.phone << endl;
    }
}


// Search contacts
void searchContacts(const string& currentUser) {
    string keyword;
    cout << "\nNhap tu khoa (ten hoac so dien thoai): ";
    cin.ignore();
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << "Tu khoa rong! Hien thi tat ca danh ba...\n";
        viewContactsFile(currentUser);
        return;
    }

    vector<Contact> contacts = loadUserContacts(currentUser);
    vector<Contact> results;

    // Convert keyword to lowercase for case-insensitive search
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    for (const auto& c : contacts) {
        string lowerName = c.name;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerKeyword) != string::npos || c.phone.find(keyword) != string::npos) {
            results.push_back(c);
        }
    }

    if (results.empty()) {
        cout << "No matching name found.\n";
        return;
    }

    cout << "\n========== KET QUA TIM KIEM ==========\n";
    cout << "Tim thay " << results.size() << " ket qua:\n\n";

    for (const auto& c : results) {
        cout << "ID: " << c.id << endl;
        cout << "Ten: " << c.name << endl;
        cout << "So dien thoai: " << c.phone << endl;
        cout << "Email: " << c.email << endl;
        cout << string(40, '-') << endl;
    }
}

// Check if phone exists for current user
bool isPhoneExists(const string& phone, const string& currentUser) {
    vector<Contact> contacts = loadUserContacts(currentUser);
    for (const auto& c : contacts) {
        if (c.phone == phone) return true;
    }
    return false;
}

// Add contact
void addContact(const string& currentUser) {
    Contact c;
    c.owner = currentUser;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n=== THEM DANH BA MOI ===\n";
    cout << "Ho va ten: ";
    getline(cin, c.name);

    if (c.name.empty()) {
        cout << "Name is required.\n";
        return;
    }

    cout << "So dien thoai: ";
    getline(cin, c.phone);

    for (char ch : c.phone) {
        if (!isdigit(ch)) {
            cout << "Phone number must be numeric.\n";
            return;
        }
    }

    if (isPhoneExists(c.phone, currentUser)) {
        cout << "This phone number already exists.\n";
        return;
    }

    cout << "Email: "; getline(cin, c.email);
    cout << "Dia chi: "; getline(cin, c.address);
    cout << "Ghi chu: "; getline(cin, c.note);

    // Generate new ID
    ifstream file(CONTACTS_FILE);
    string line, lastID = "0";
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, lastID, '|');
    }
    file.close();

    c.id = to_string(stoi(lastID) + 1);

    ofstream out("Contacts.txt", ios::app);
    out << c.id << "|" << c.owner << "|" << c.name << "|" << c.phone << "|"
        << c.email << "|" << c.address << "|" << c.note << endl;

    out.close();

    cout << "Contact added successfully.\n";
}

void sortContactsByName(vector<Contact>& contacts) {
    sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.name < b.name;
        });
}

// Update contact
void updateContact(const string& currentUser) {
    string id;
    cout << "\nNhap ID danh ba can cap nhat: ";
    cin >> id;

    ifstream file(CONTACTS_FILE);
    ofstream temp("temp.txt");

    string line;
    bool updated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;

        getline(ss, c.id, '|');
        getline(ss, c.owner, '|');
        getline(ss, c.name, '|');
        getline(ss, c.phone, '|');
        getline(ss, c.email, '|');
        getline(ss, c.address, '|');
        getline(ss, c.note, '|');

        if (c.id == id && c.owner == currentUser) {
            cin.ignore();
            cout << "Ten moi (hien tai: " << c.name << "): ";
            getline(cin, c.name);
            cout << "So dien thoai moi (hien tai: " << c.phone << "): ";
            getline(cin, c.phone);
            cout << "Ghi chu moi (hien tai: " << c.note << "): ";
            getline(cin, c.note);

            updated = true;
        }

        temp << c.id << "|" << c.owner << "|" << c.name << "|" << c.phone << "|"
            << c.email << "|" << c.address << "|" << c.note << endl;

    }

    file.close();
    temp.close();

    remove(CONTACTS_FILE.c_str());
    rename("temp.txt", CONTACTS_FILE.c_str());

    if (updated)
        cout << "Contact updated successfully.\n";
    else
        cout << "Contact not found or you don't have permission.\n";
}

// Delete single contact
void deleteContact(const string& currentUser) {
    string id;
    cout << "\nNhap ID danh ba can xoa: ";
    cin >> id;

    ifstream file(CONTACTS_FILE);
    ofstream temp("temp.txt");

    string line;
    bool deleted = false;

    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;

        getline(ss, c.id, '|');
        getline(ss, c.owner, '|');

        if (c.id == id && c.owner == currentUser) {
            deleted = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove(CONTACTS_FILE.c_str());
    rename("temp.txt", CONTACTS_FILE.c_str());

    if (deleted)
        cout << "Contact deleted successfully.\n";
    else
        cout << "Contact not found or you don't have permission.\n";
}

// Delete multiple contacts
void deleteMultipleContacts(const string& currentUser) {
    string ids;
    cout << "\nNhap cac ID can xoa (cach nhau boi dau phay): ";
    cin.ignore();
    getline(cin, ids);

    // Parse IDs
    vector<string> idList;
    stringstream ss(ids);
    string id;
    while (getline(ss, id, ',')) {
        // Trim whitespace
        id.erase(0, id.find_first_not_of(" \t"));
        id.erase(id.find_last_not_of(" \t") + 1);
        idList.push_back(id);
    }

    ifstream file(CONTACTS_FILE);
    ofstream temp("temp.txt");

    string line;
    int deletedCount = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;

        getline(ss, c.id, '|');
        getline(ss, c.owner, '|');

        bool shouldDelete = false;
        if (c.owner == currentUser) {
            for (const auto& delId : idList) {
                if (c.id == delId) {
                    shouldDelete = true;
                    deletedCount++;
                    break;
                }
            }
        }

        if (!shouldDelete) {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove(CONTACTS_FILE.c_str());
    rename("temp.txt", CONTACTS_FILE.c_str());

    cout << "Deleted " << deletedCount << " contact(s) successfully.\n";
}
