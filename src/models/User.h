#pragma once
#include <drogon/drogon.h>
#include <json/json.h>

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

    User(const std::shared_ptr<Json::Value> &userJson) 
    {
        id = userJson->get("id", 0).asInt();
        name = userJson->get("name", "").asString();
    }
};