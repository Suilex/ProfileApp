#pragma once
#include <drogon/HttpFilter.h>
#include <jwt-cpp/jwt.h>

class JwtMiddleware : public drogon::HttpFilter<JwtMiddleware> {
public:
    JwtMiddleware(){};

    void doFilter(const drogon::HttpRequestPtr &req, 
                    drogon::FilterCallback &&fcb, drogon::FilterChainCallback &&fccb) override {
        auto authHeader = req->getHeader("Authorization");

        if (authHeader.empty() || authHeader.find("Bearer ") != 0) {
            auto res = drogon::HttpResponse::newHttpResponse();
            res->setStatusCode(drogon::k401Unauthorized);
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
            auto res = drogon::HttpResponse::newHttpResponse();
            res->setStatusCode(drogon::k401Unauthorized);
            res->setBody("Unauthorized: Invalid token");
            fcb(res);
        }
    }
};