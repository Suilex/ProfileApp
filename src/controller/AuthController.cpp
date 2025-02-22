#include <drogon/drogon.h>
#include "AuthController.h"
#include "../service/AuthService.h"

void AuthController::login(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) 
{
    std::string userId = req->getParameter("user_id");
    Json::Value json;

    try 
    {
        json["token"] = auth_service.generateToken(userId);
    } 
    catch (const std::runtime_error &e)
    {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k400BadRequest);
        response->setBody(e.what());
        callback(response);
        return;
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
    response->setStatusCode(drogon::k201Created);
    response->setBody(json.toStyledString());
    callback(response);
}

