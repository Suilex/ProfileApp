#include <drogon/drogon.h>
#include <json/json.h>
#include "UserRepository.h"

UserRepository::UserRepository(const drogon::orm::DbClientPtr &client) 
    : db_client(client) {} 

std::vector<User> UserRepository::getAllUsers() {
    drogon::orm::Result result = db_client->execSqlSync("SELECT * FROM User");
    std::vector<User> users;
    for (const auto &row : result) {
        users.push_back(row);
    }
    return users;
}

void UserRepository::addUser(const User &user) {
    db_client->execSqlSync("INSERT INTO User (name) VALUES ($1)", user.name);
}