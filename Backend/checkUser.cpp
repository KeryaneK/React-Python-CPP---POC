#include <iostream>
#include "sqlite3.h"
#include <string>

/*
Gets:
login
password

Returns:
OK
NOT_OK
ERROR
*/

bool checkUser(sqlite3 *db, const std::string& login, const std::string& password) {
    std::string sqlStatement = "SELECT password FROM users WHERE login = '" + login + "';";
    std::string storedPassword;
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void *data, int argc, char **argv, char **azColName) {
        std::string *storedPassword = static_cast<std::string*>(data);
        if (argc > 0 && argv[0])
            *storedPassword = argv[0];
        return SQLITE_OK;
    }, &storedPassword, &errMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    return storedPassword == password;
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

    if (checkUser(db, login, password)) {
        std::cout << "OK";
    }
    else {
        std::cout << "NOT_OK";
    }

    sqlite3_close(db);

    return 0;
}