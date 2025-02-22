#pragma once
#include <drogon/HttpFilter.h>
#include <jwt-cpp/jwt.h>

using namespace drogon;

class JwtMiddleware : public HttpFilter<JwtMiddleware> {
public:
    JwtMiddleware(){};

    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override {
        auto authHeader = req->getHeader("Authorization");

        if (authHeader.empty() || authHeader.find("Bearer ") != 0) {
            auto res = HttpResponse::newHttpResponse();
            res->setStatusCode(k401Unauthorized);
            res->setBody("Unauthorized: Missing Bearer token");
            fcb(res);
            return;
        }

        std::string token = authHeader.substr(7);
        try {
            auto decoded = jwt::decode(token);
            req->attributes()->insert("user_id", decoded.get_payload_claim("user_id").as_string());
            fccb();
        } catch (const std::exception &e) {
            auto res = HttpResponse::newHttpResponse();
            res->setStatusCode(k401Unauthorized);
            res->setBody("Unauthorized: Invalid token");
            fcb(res);
        }
    }
};