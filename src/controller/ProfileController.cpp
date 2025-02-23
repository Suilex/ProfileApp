#include "ProfileController.h"
#include <drogon/drogon.h>
#include "../service/ProfileService.h"

void ProfileController::getAllUsers(const drogon::HttpRequestPtr &req,
                                 std::function<void(const drogon::HttpResponsePtr &)> &&callback) 
{
    Json::Value users = profileService.getAllUser();
    
    auto response = drogon::HttpResponse::newHttpJsonResponse(users);
    response->setStatusCode(drogon::k200OK);
    callback(response);
}

void ProfileController::addUser(const drogon::HttpRequestPtr &req,
                             std::function<void(const drogon::HttpResponsePtr &)> &&callback) 
{
    auto requestBody = req->getJsonObject();

    try 
    {
        profileService.addUser(requestBody);
    } 
    catch (const std::exception &e) 
    {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k500InternalServerError);
        response->setBody(e.what());
        callback(response);
        return;
    }

    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::k201Created);
    callback(response);
}
