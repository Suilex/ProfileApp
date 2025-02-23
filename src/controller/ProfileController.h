#pragma once
#include <drogon/HttpController.h>
#include "../utils/JwtMiddleware.h"
#include "../service/ProfileService.h"

class ProfileController : public drogon::HttpController<ProfileController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ProfileController::getAllUsers, "/users/all", drogon::Get, "JwtMiddleware"); 
    ADD_METHOD_TO(ProfileController::addUser, "/users/add", drogon::Post, "JwtMiddleware");
    METHOD_LIST_END

    void getAllUsers(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);
    void addUser(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

private:
    ProfileService profileService;
};