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

class PostManager {
private:
    sqlite3* db;

public:
    PostManager() : db(nullptr) {}

    ~PostManager() {
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

    bool addPost(const std::string& title, const std::string& content, const std::string& userId) {
        char* errMsg = nullptr;
        std::string sqlStatement = "INSERT INTO posts (title, content, user_id) VALUES ('" + title + "', '" + content + "', '" + userId + "');";

        int rc = sqlite3_exec(db, sqlStatement.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cout << "ERROR";
            sqlite3_free(errMsg);
            return false; // Error
        } else {
            std::cout << "OK";
            return true; // OK
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "ERROR";
        return 1;
    }

    std::string title = argv[1];
    std::string content = argv[2];
    std::string user_id = argv[3];

    PostManager postManager;
    if (!postManager.openDatabase("database.db")) {
        return 1;
    }

    if (!postManager.addPost(title, content, user_id)) {
        return 1;
    }

    return 0;
}