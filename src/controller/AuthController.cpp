#include <drogon/drogon.h>
#include "AuthController.h"
#include "../service/AuthService.h"

void AuthController::login(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) 
{
    std::string user_id = req->getParameter("user_id");

    if (user_id.empty() || user_id.length() > 1000) 
    {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k400BadRequest);
        response->setBody("Missing 'user_id' parameter");
        callback(response);
        return;
    }

    std::string jwtToken;
    try 
    {
        jwtToken = auth_service.generateToken(user_id);
    } 
    catch (const std::exception &e)
    {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k500InternalServerError);
        response->setBody(e.what());
        callback(response);
        return;
    }

    drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpResponse();
    Json::Value json;
    json["token"] = jwtToken;
    response->setStatusCode(drogon::k201Created);
    response->setBody(json.toStyledString());
    callback(response);
}

