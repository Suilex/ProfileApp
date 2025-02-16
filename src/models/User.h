#pragma once
#include <drogon/drogon.h>

class User {
public:
    int id;
    std::string name;

    User() = default;
    User(int id, const std::string &name) : id(id), name(name) {}

    User(const drogon::orm::Row &row) {  
        id = row["id"].as<int>();
        name = row["name"].as<std::string>();
    }
};