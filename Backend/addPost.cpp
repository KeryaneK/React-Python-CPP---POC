#include <iostream>
#include "sqlite3.h"
#include <string>

/*
Gets:
title
content
user_id

Returns:
OK
ERROR
*/

bool addPost(sqlite3 *db, const std::string& title, const std::string& content, std::string userId) {
    char *errMsg = nullptr;
    std::string sqlStatement = "INSERT INTO posts (title, content, user_id) VALUES ('" + title + "', '" + content + "', " + userId + ");";

    int rc = sqlite3_exec(db, sqlStatement.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false; // Error
    } else {
        return true; // OK
    }
}

int main(int argc, char *argv[]) {
    std::string title = argv[1];
    std::string content = argv[2];
    std::string user_id = argv[3];

    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        std::cout << "ERROR";
        return 1;
    } else {
    }

    if (addPost(db, title, content, user_id) == false) {
        std::cout << "ERROR";
        return 1;
    };

    std::cout << "OK";

    sqlite3_close(db);

    return 0;
}