#include "ProfileController.h"
#include <drogon/drogon.h>
#include "../repository/UserRepository.h"

ProfileController::ProfileController()    
    : repo(drogon::app().getDbClient()) {} 

void ProfileController::getAllUsers(const drogon::HttpRequestPtr &req,
                                 std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    std::vector<User> users = repo.getAllUsers();
    Json::Value json;

    for (const auto &user : users) {
        Json::Value jsonUser;
        jsonUser["id"] = user.id;
        jsonUser["name"] = user.name;
        json.append(jsonUser);
    }
    
    auto response = drogon::HttpResponse::newHttpJsonResponse(json);
    callback(response);
}

void ProfileController::addUser(const drogon::HttpRequestPtr &req,
                             std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();

    if (!json || !json->isMember("name")) {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    User newUser(0, (*json)["name"].asString());
    repo.addUser(newUser);

    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::k201Created);
    callback(response);
}
