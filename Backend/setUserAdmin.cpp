#include <iostream>
#include "sqlite3.h"
#include <string>

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

    bool setUserAsAdmin(const std::string& userId) {
        std::string sqlStatement = "UPDATE users SET isAdmin = 1 WHERE id = " + userId + ";";

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        return true;
    }

private:
    sqlite3* db;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: User ID not provided" << std::endl;
        return 1;
    }

    std::string userId = argv[1];

    UserManager userManager;
    if (!userManager.openDatabase("database.db")) {
        return 1;
    }

    if (userManager.setUserAsAdmin(userId)) {
        std::cout << "User with ID " << userId << " set as admin successfully" << std::endl;
    } else {
        std::cerr << "Failed to set user with ID " << userId << " as admin" << std::endl;
        return 1;
    }

    return 0;
}