#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "Authentication.h"

using namespace std;


void loadUsers(vector<User>& users, const string& filename) {
    users.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string u, p, e;
        if (getline(ss, u, '|') && getline(ss, p, '|') && getline(ss, e)) {
            users.push_back({ u, p, e });
        }
    }
    file.close();
}

void saveUsers(const vector<User>& users, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& u : users) {
        file << u.username << "|" << u.password << "|" << u.email << endl;
    }
    file.close();
}

bool registerUser(vector<User>& users, const string& filename) {
    User u;
    cout << "\n=== DANG KY TAI KHOAN ===" << endl;
    cout << "Username: ";
    cin >> u.username;

    // Check if username exists
    for (const auto& user : users) {
        if (user.username == u.username) {
            cout << "Loi: Username da ton tai!" << endl;
            return false;
        }
    }

    cout << "Password: ";
    cin >> u.password;


    cout << "Email: ";
    cin >> u.email;

    users.push_back(u);
    saveUsers(users, filename);
    cout << "Dang ky thanh cong!" << endl;
    return true;
}

bool loginUser(vector<User>& users, const string& filename, string& loggedInUser) {
    while (true) {
        string u, p;
        cout << "\n=== DANG NHAP ===" << endl;
        cout << "Username (nhap 0 de thoat): ";
        cin >> u;

        if (u == "0") return false;

        cout << "Password: ";
        cin >> p;

        string hashedPassword = p;

        for (const auto& user : users) {
            if (user.username == u && user.password == hashedPassword) {
                loggedInUser = u;
                cout << "\nDang nhap thanh cong! Xin chao " << u << "!" << endl;
                return true;
            }
        }

        cout << "\n Sai thong tin dang nhap!\n";
        cout << "1. Dang nhap lai\n";
        cout << "2. Thoat\n";
        cout << "3. Dang ky\n";
        cout << "Lua chon: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            continue;
        }
        else if (choice == 2) {
            return false;
        }
        else if (choice == 3) {
            registerUser(users, filename);
            // sau khi đăng ký xong → quay lại đăng nhập
        }
        else {
            cout << "Lua chon khong hop le!\n";
        }
    }
}



bool updateUserInfo(vector<User>& users, const string& username, const string& filename) {
    string newEmail;
    cout << "\n=== CAP NHAT THONG TIN ===" << endl;
    cout << "Email moi: ";
    cin.ignore();
    getline(cin, newEmail);

    for (auto& user : users) {
        if (user.username == username) {
            user.email = newEmail;
            saveUsers(users, filename);
            cout << "Cap nhat thanh cong!" << endl;
            return true;
        }
    }
    return false;
}

bool changePassword(vector<User>& users, const string& username, const string& filename) {
    string oldPass, newPass, confirmPass;
    cout << "\n=== DOI MAT KHAU ===" << endl;
    cout << "Mat khau cu: "; cin >> oldPass;

    // Check mật khẩu
    string hashedOldPass = oldPass;

    // Tìm user và xác nhận mật khẩu cũ
    for (auto& user : users) {
        if (user.username == username) {
            if (user.password != hashedOldPass) {
                cout << "Mat khau cu khong dung!" << endl;
                return false;
            }

            cout << "Mat khau moi: "; cin >> newPass;
            cout << "Xac nhan mat khau moi: "; cin >> confirmPass;

            if (newPass != confirmPass) {
                cout << "Mat khau xac nhan khong khop!" << endl;
                return false;
            }

            // Băm mật khẩu mới trước khi lưu
            user.password = newPass;
            saveUsers(users, filename);
            cout << "Doi mat khau thanh cong!" << endl;
            return true;
        }
    }
    return false;
}
