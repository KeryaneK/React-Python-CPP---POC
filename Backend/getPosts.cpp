#include <iostream>
#include "sqlite3.h"
#include <string>
#include <vector>

/*
Gets:
user (optional)

Returns:
[{id, title, content, user}]
NO_POSTS
ERROR
*/

struct Post {
    int id;
    std::string title;
    std::string content;
    std::string user;
};

std::vector<Post> getPosts(sqlite3 *db, std::string& user_id) {
    std::vector<Post> posts;
    std::string sqlStatement;

    if (user_id == "all") {
        sqlStatement = "SELECT posts.id, posts.title, posts.content, users.login FROM posts JOIN users ON posts.user_id = users.id;";
    } else {
        sqlStatement = "SELECT posts.id, posts.title, posts.content, users.login FROM posts JOIN users ON posts.user_id = users.id WHERE users.id = " + user_id + ";";
    }


    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void *data, int argc, char **argv, char **azColName) {
        std::vector<Post> *posts = static_cast<std::vector<Post>*>(data);
        Post post;
        post.id = std::stoi(argv[0]);
        post.title = argv[1];
        post.content = argv[2];
        post.user = argv[3];
        posts->push_back(post);
        return SQLITE_OK;
    }, &posts, &errMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        // Return an empty vector to indicate error
        return {};
    }

    return posts;
}

int main(int argc, char *argv[]) {
    std::string user_id = argv[1];

    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        // Print 'ERROR' and exit
        std::cout << "ERROR";
        return 1;
    }

    std::vector<Post> posts = getPosts(db, user_id);

    // Check if posts vector is empty (indicating error)
    if (posts.empty()) {
        std::cout << "NO_POSTS";
    } else {
        // Print the posts
        std::cout << "[";
        for (const auto& post : posts) {
            std::cout << "{";
            std::cout << "id:" << post.id << ",";
            std::cout << "title:" << post.title << ",";
            std::cout << "content:" << post.content << ",";
            std::cout << "user:" << post.user;
            std::cout << "},";
        }
        std::cout << "]";
    }

    sqlite3_close(db);

    return 0;
}