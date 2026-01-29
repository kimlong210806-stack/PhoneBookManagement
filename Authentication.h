#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <vector>
using namespace std;

struct User {
    string username;
    string password;
    string email;
};

void loadUsers(vector<User>& users, const string& filename);
void saveUsers(const vector<User>& users, const string& filename);
bool registerUser(vector<User>& users, const string& filename);
bool loginUser(vector<User>& users, const string& filename, string& loggedInUser);



bool updateUserInfo(std::vector<User>& users, const std::string& username, const std::string& filename);
bool changePassword(std::vector<User>& users, const std::string& username, const std::string& filename);

#endif
