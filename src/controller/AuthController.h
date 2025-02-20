#pragma once
#include <drogon/HttpController.h>
#include "../service/AuthService.h"

class AuthController : public drogon::HttpController<AuthController> {
public:

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AuthController::login, "/login", drogon::Get);
    METHOD_LIST_END

    void login(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);
private:
    AuthService auth_service;
};