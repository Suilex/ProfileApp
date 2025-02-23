#include "ProfileService.h"
#include "../models/User.h"
#include "../repository/UserRepository.h"
#include <json/json.h>

ProfileService::ProfileService()    
    : repo(drogon::app().getDbClient()) {} 


Json::Value ProfileService::getAllUser() 
{
    std::vector<User> users = repo.getAllUsers();
    Json::Value usersJson;

    for (const auto &user : users) 
    {
        Json::Value userJson;
        userJson["id"] = user.id;
        userJson["name"] = user.name;
        usersJson.append(userJson);
    }

    return usersJson;
}

void ProfileService::addUser(const std::shared_ptr<Json::Value> &user) 
{
    if (!user || !user->isMember("name")) 
    {
        throw std::invalid_argument("Invalid user data: 'name' is required.");
    }

    User newUser(user);
    repo.addUser(newUser);
}