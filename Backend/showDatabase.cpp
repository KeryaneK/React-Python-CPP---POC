#include <iostream>
#include "sqlite3.h"
#include <string>

// Callback function to print query results
int printCallback(void *data, int argc, char **argv, char **colName) {
    std::cout << "-------------------" << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << colName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

// Function to print entire contents of the users table
void printUsers(sqlite3 *db) {
    char *errMsg = nullptr;
    std::string sqlStatement = "SELECT * FROM users;";
    int rc = sqlite3_exec(db, sqlStatement.c_str(), printCallback, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Function to print entire contents of the posts table
void printPosts(sqlite3 *db) {
    char *errMsg = nullptr;
    std::string sqlStatement = "SELECT * FROM posts;";
    int rc = sqlite3_exec(db, sqlStatement.c_str(), printCallback, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::cout << "Users Table:" << std::endl;
    printUsers(db);
    
    std::cout << "\nPosts Table:" << std::endl;
    printPosts(db);

    sqlite3_close(db);

    return 0;
}