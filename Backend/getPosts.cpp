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

    std::vector<Post> getPosts(const std::string& user_id) {
        std::vector<Post> posts;
        std::string sqlStatement;

        if (user_id == "all") {
            sqlStatement = "SELECT posts.id, posts.title, posts.content, users.login FROM posts JOIN users ON posts.user_id = users.id;";
        } else {
            sqlStatement = "SELECT posts.id, posts.title, posts.content, users.login FROM posts JOIN users ON posts.user_id = users.id WHERE users.id = " + user_id + ";";
        }

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Post>* posts = static_cast<std::vector<Post>*>(data);
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
            return {};
        }

        return posts;
    }

private:
    sqlite3* db;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR";
        return 1;
    }

    std::string user_id = argv[1];

    PostManager postManager;
    if (!postManager.openDatabase("database.db")) {
        return 1;
    }

    std::vector<Post> posts = postManager.getPosts(user_id);

    if (posts.empty()) {
        std::cout << "NO_POSTS";
    } else {
        std::cout << "[";
        for (size_t i = 0; i < posts.size(); ++i) {
            const auto& post = posts[i];
            std::cout << "{";
            std::cout << "\"id\":" << post.id << ",";
            std::cout << "\"title\":\"" << post.title << "\",";
            std::cout << "\"content\":\"" << post.content << "\",";
            std::cout << "\"user\":\"" << post.user << "\"";
            std::cout << "}";
            if (i != posts.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]";
    }

    return 0;
}