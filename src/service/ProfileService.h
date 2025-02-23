#pragma once
#include "../repository/UserRepository.h"
#include <json/json.h>

class ProfileService 
{
public:
    ProfileService();
    void addUser(const std::shared_ptr<Json::Value> &user);
    Json::Value getAllUser();    

private:
    UserRepository repo;
};