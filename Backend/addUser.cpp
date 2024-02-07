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

bool usernameExists(sqlite3 *db, const std::string& login) {
    std::string sqlStatement = "SELECT COUNT(*) FROM users WHERE login = '" + login + "';";
    int result;
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void *data, int argc, char **argv, char **azColName) {
        int *result = static_cast<int*>(data);
        *result = atoi(argv[0]); // Extract count from the result
        return SQLITE_OK;
    }, &result, &errMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    return result > 0;
}

void addUser(sqlite3 *db, const std::string& login, const std::string& password) {
    if (usernameExists(db, login)) {
        std::cout << "USER_EXISTS";
        return;
    }

    char *errMsg = 0;
    std::string sqlStatement = "INSERT INTO users (login, password) VALUES ('" + login + "', '" + password + "');";

    int rc = sqlite3_exec(db, sqlStatement.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cout << "ERROR";
        sqlite3_free(errMsg);
    } else {
        std::cout << "OK";
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

    // Example usage: add a user only if the username doesn't already exist
    addUser(db, login, password);

    // Close database
    sqlite3_close(db);

    return 0;
}