#include <iostream>
#include "sqlite3.h"

int main() {
    sqlite3 *db;
    char *errMsg = 0;

    // Open database (create if not exists)
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // Create users table
    const char *createUsersTableSQL = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "login TEXT NOT NULL,"
        "password TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, createUsersTableSQL, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Users table created successfully" << std::endl;
    }

    // Create posts table
    const char *createPostsTableSQL = 
        "CREATE TABLE IF NOT EXISTS posts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "content TEXT NOT NULL,"
        "user_id INTEGER NOT NULL,"
        "FOREIGN KEY (user_id) REFERENCES users(id));";
    
    rc = sqlite3_exec(db, createPostsTableSQL, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Posts table created successfully" << std::endl;
    }

    // Close database
    sqlite3_close(db);

    return 0;
}