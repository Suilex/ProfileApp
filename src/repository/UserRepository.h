#pragma once
#include "drogon/drogon.h"
#include "../models/User.h"
#include <drogon/orm/Mapper.h>

class UserRepository
{
private:
    drogon::orm::DbClientPtr db_client;
    
public:
    UserRepository(const drogon::orm::DbClientPtr &client);

    std::vector<User> getAllUsers();
    void addUser(const User &user);
};
