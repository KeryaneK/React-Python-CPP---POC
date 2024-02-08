#include <iostream>
#include "sqlite3.h"
#include <string>

/*
Gets:
user_id
post_id

Returns:
OK
ERROR
*/

bool deletePost(sqlite3 *db, const std::string& user_id, const std::string& post_id) {
    std::string sqlStatement = "DELETE FROM posts WHERE user_id = " + user_id + " AND id = " + post_id + ";";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    if (sqlite3_changes(db) == 0) {
        return false;
    }

    return true; // OK
}

int main(int argc, char *argv[]) {
    std::string user_id = argv[1];
    std::string post_id = argv[2];

    sqlite3 *db;
    char *errMsg = nullptr;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        std::cout << "ERROR";
        return 1;
    }

    // Call deletePost function
    if (deletePost(db, user_id, post_id)) {
        std::cout << "OK";
    } else {
        std::cout << "ERROR";
    }

    sqlite3_close(db);

    return 0;
}