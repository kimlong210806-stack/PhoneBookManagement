#include <iostream>
#include "Authentication.h"
#include <vector>
#include "Menu.h"

using namespace std;

vector<User> users;
string userFile = "User.txt";

int main() {
    string loggedInUser;

    cout << "========================================\n";
    cout << "   PHONE BOOK MANAGEMENT SYSTEM\n";
    cout << "   Welcome Group 04!\n";
    cout << "========================================\n";

    // Load users from file
    loadUsers(users, userFile);

    int choice;
    bool isLoggedIn = false;

    // Authentication loop
    while (!isLoggedIn) {
        cout << "\n=== HE THONG QUAN LY DANH BA ===\n";
        cout << "1. Dang ky tai khoan\n";
        cout << "2. Dang nhap\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser(users, userFile);
            break;
        case 2:
            if (loginUser(users, userFile, loggedInUser)) {
                isLoggedIn = true;
            }
            break;
        case 0:
            cout << "Tam biet!\n";
            return 0;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    }

    showMainMenu(loggedInUser);

    return 0;
}
