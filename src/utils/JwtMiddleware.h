#pragma once
#include <drogon/HttpFilter.h>
#include <jwt-cpp/jwt.h>

class JwtMiddleware : public drogon::HttpFilter<JwtMiddleware> {
public:
    JwtMiddleware(){};

    void doFilter(const drogon::HttpRequestPtr &req, 
                    drogon::FilterCallback &&fcb, drogon::FilterChainCallback &&fccb) override {
        auto authHeader = req->getHeader("Authorization");
        auto config = drogon::app().getCustomConfig();

        if (authHeader.empty() || authHeader.find("Bearer ") != 0) {
            auto res = drogon::HttpResponse::newHttpResponse();
            res->setStatusCode(drogon::k401Unauthorized);
            res->setBody("Unauthorized: Missing Bearer token");
            fcb(res);
            return;
        }
        else if (!config.isMember("jwt") || !config["jwt"].isMember("issuer") || !config["jwt"].isMember("secret"))
        {
            auto res = drogon::HttpResponse::newHttpResponse();
            res->setStatusCode(drogon::k500InternalServerError);
            res->setBody("Server configuration error: Missing JWT settings");
            fcb(res);
            return;
        }

        std::string secretKey = config["jwt"]["secret"].asString();
        std::string issuer = config["jwt"]["issuer"].asString();
        std::string tokenWithoutBearer = authHeader.substr(7);
        try {
            auto decoded = jwt::decode(tokenWithoutBearer);
            auto verifier = jwt::verify()
                                .allow_algorithm(jwt::algorithm::hs256{secretKey})
                                .with_issuer(issuer);

            verifier.verify(decoded);
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