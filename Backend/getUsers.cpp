#include <iostream>
#include "sqlite3.h"
#include <string>
#include <vector>
#include <map>

class UserManager {
public:
    UserManager() : db(nullptr) {}

    ~UserManager() {
        if (db)
            sqlite3_close(db);
    }

    bool openDatabase(const char* dbName) {
        int rc = sqlite3_open(dbName, &db);
        if (rc != SQLITE_OK) {
            std::cout << "ERROR";
            return false;
        }
        return true;
    }

    std::vector<std::map<std::string, std::string>> getUsers() {
        std::vector<std::map<std::string, std::string>> users;
        std::string sqlStatement = "SELECT id, login, isAdmin FROM users;";

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
            std::vector<std::map<std::string, std::string>>* users = static_cast<std::vector<std::map<std::string, std::string>>*>(data);
            std::map<std::string, std::string> user;
            user["id"] = argv[0];
            user["login"] = argv[1];
            user["isAdmin"] = argv[2];
            users->push_back(user);
            return SQLITE_OK;
        }, &users, &errMsg);

        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
            return {};
        }

        return users;
    }

private:
    sqlite3* db;
};

int main(int argc, char* argv[]) {
    UserManager userManager;
    if (!userManager.openDatabase("database.db")) {
        return 1;
    }

    std::vector<std::map<std::string, std::string>> users = userManager.getUsers();

    if (users.empty()) {
        std::cout << "NO_USERS";
    } else {
        std::cout << "[";
        for (size_t i = 0; i < users.size(); ++i) {
            const auto& user = users[i];
            std::cout << "{";
            std::cout << "\"id\":\"" << user.at("id") << "\",";
            std::cout << "\"login\":\"" << user.at("login") << "\",";
            std::cout << "\"isAdmin\":\"" << user.at("isAdmin") << "\"";
            std::cout << "}";
            if (i != users.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]";
    }

    return 0;
}