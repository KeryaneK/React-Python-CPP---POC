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

void checkUser(sqlite3 *db, const std::string& login, const std::string& password) {
    std::string sqlStatement = "SELECT id, password FROM users WHERE login = '" + login + "';";
    int id = -1; // Default value if not found
    std::string storedPassword;
    std::tuple<std::string*, int*> userData(&storedPassword, &id);
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void *data, int argc, char **argv, char **azColName) {
        auto userData = *static_cast<std::tuple<std::string*, int*>*>(data);
        if (argc > 0 && argv[1])
            *std::get<0>(userData) = argv[1]; // Assign char* to std::string
        if (argc > 1 && argv[0])
            *std::get<1>(userData) = std::stoi(argv[0]);
        return SQLITE_OK;
    }, &userData, &errMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        std::cout << "ERROR";
        return;
    }

    if (storedPassword == password) {
        std::cout << id;
    } else {
        std::cout << "NOT_OK";
    }
}

int main(int argc, char *argv[]) {
    std::string login = argv[1];
    std::string password = argv[2];

    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        std::cout << "ERROR";
        return 1;
    }

    checkUser(db, login, password);

    sqlite3_close(db);

    return 0;
}