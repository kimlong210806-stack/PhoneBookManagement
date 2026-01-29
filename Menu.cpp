#include <iostream>
#include <vector>
#include "Authentication.h"
#include "Backend.h"
#include "Menu.h"

using namespace std;

extern vector<User> users;
extern string userFile;

void showAccountMenu(const string& currentUser) {
    int choice;

    do {
        cout << "\n====== QUAN LY TAI KHOAN ======\n";
        cout << "1. Cap nhat thong tin\n";
        cout << "2. Doi mat khau\n";
        cout << "0. Quay lai\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            updateUserInfo(users, currentUser, userFile);
            break;
        case 2:
            changePassword(users, currentUser, userFile);
            break;
        case 0:
            cout << "Quay lai menu chinh...\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

void showMainMenu(const string& currentUser) {
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "   PHONE BOOK MANAGEMENT SYSTEM\n";
        cout << "   User: " << currentUser << "\n";
        cout << "========================================\n";
        cout << "1. Xem tat ca danh ba\n";
        cout << "2. Xem danh ba (sap xep theo ten)\n";
        cout << "3. Xem chi tiet danh ba\n";
        cout << "4. Tim kiem danh ba\n";
        cout << "5. Them danh ba moi\n";
        cout << "6. Cap nhat danh ba\n";
        cout << "7. Xoa danh ba\n";
        cout << "8. Xoa nhieu danh ba\n";
        cout << "9. Quan ly tai khoan\n";
        cout << "0. Dang xuat\n";
        cout << "========================================\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewContactsFile(currentUser);
            break;
        case 2:
            viewContactsSorted(currentUser);
            break;
        case 3:
            viewContactDetails(currentUser);
            break;
        case 4:
            searchContacts(currentUser);
            break;
        case 5:
            addContact(currentUser);
            break;
        case 6:
            updateContact(currentUser);
            break;
        case 7:
            deleteContact(currentUser);
            break;
        case 8:
            deleteMultipleContacts(currentUser);
            break;
        case 9:
            showAccountMenu(currentUser);
            break;
        case 0:
            cout << "Dang xuat thanh cong. Tam biet!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}
