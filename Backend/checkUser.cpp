#include <iostream>
#include "sqlite3.h"
#include <string>
#include <tuple>

/*
Gets:
login
password

Returns:
OK
NOT_OK
ERROR
*/

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

    void checkUser(const std::string& login, const std::string& password) {
        std::string sqlStatement = "SELECT id, password, isAdmin FROM users WHERE login = '" + login + "';";
        int id = -1; // Default value if not found
        std::string storedPassword;
        int isAdmin = 0; // Default value for isAdmin
        std::tuple<std::string*, int*, int*> userData(&storedPassword, &id, &isAdmin);

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
            auto userData = *static_cast<std::tuple<std::string*, int*, int*>*>(data);
            if (argc > 0 && argv[1])
                *std::get<0>(userData) = argv[1];
            if (argc > 1 && argv[0])
                *std::get<1>(userData) = std::stoi(argv[0]);
            if (argc > 2 && argv[2])
                *std::get<2>(userData) = std::stoi(argv[2]);
            return SQLITE_OK;
        }, &userData, &errMsg);

        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
            std::cout << "ERROR";
            return;
        }

        if (storedPassword == password) {
            std::cout << id << "," << isAdmin;
        } else {
            std::cout << "NOT_OK";
        }
    }

private:
    sqlite3* db;
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

    userManager.checkUser(login, password);

    return 0;
}