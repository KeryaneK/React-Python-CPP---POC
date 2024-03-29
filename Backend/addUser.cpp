#include <iostream>
#include "sqlite3.h"
#include <string>

/*
Gets:
login
password

Returns:
OK
USER_EXISTS
ERROR
*/

class UserManager {
private:
    sqlite3* db;

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

    bool usernameExists(const std::string& login) {
        std::string sqlStatement = "SELECT COUNT(*) FROM users WHERE login = '" + login + "';";
        int result;

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
            int* result = static_cast<int*>(data);
            *result = atoi(argv[0]); // Extract count from the result
            return SQLITE_OK;
        }, &result, &errMsg);

        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
            return false;
        }

        return result > 0;
    }

    void addUser(const std::string& login, const std::string& password) {
        if (usernameExists(login)) {
            std::cout << "USER_EXISTS";
            return;
        }

        char* errMsg = nullptr;
        std::string sqlStatement = "INSERT INTO users (login, password) VALUES ('" + login + "', '" + password + "');";

        int rc = sqlite3_exec(db, sqlStatement.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cout << "ERROR";
            sqlite3_free(errMsg);
        } else {
            std::cout << "OK";
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR";
        return 1;
    }

    std::string login = argv[1];
    std::string password = argv[2];

    UserManager userManager;
    if (!userManager.openDatabase("database.db")) {
        return 1;
    }

    userManager.addUser(login, password);

    return 0;
}