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

class PostManager {
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

    bool deletePost(const std::string& user_id, const std::string& post_id) {
        std::string sqlStatement = "DELETE FROM posts WHERE user_id = " + user_id + " AND id = " + post_id + ";";

        char* errMsg = nullptr;
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

private:
    sqlite3* db;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR";
        return 1;
    }

    std::string user_id = argv[1];
    std::string post_id = argv[2];

    PostManager postManager;
    if (!postManager.openDatabase("database.db")) {
        return 1;
    }

    if (postManager.deletePost(user_id, post_id)) {
        std::cout << "OK";
    } else {
        std::cout << "ERROR";
    }

    return 0;
}