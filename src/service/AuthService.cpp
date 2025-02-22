#include <jwt-cpp/jwt.h>
#include "AuthService.h"
#include <drogon/drogon.h>


std::string AuthService::generateToken(const std::string &userId)
{
    auto config = drogon::app().getCustomConfig();

    if (userId.empty() || userId.length() > 1000) 
    {
        throw std::runtime_error("Missing 'user_id' parameter");
    } 
    else if (!config["jwt"] || !config["jwt"]["issuer"] || !config["jwt"]["secret"])
    {
        throw std::runtime_error("Failed to generate JWT token. Do not find server config");
    }

    std::string issuer = config["jwt"]["issuer"].asString();
    std::string secretKey = config["jwt"]["secret"].asString();

    std::string token = jwt::create()
                    .set_issuer(issuer)
                    .set_type("JWT")
                    .set_subject("auth")
                    .set_payload_claim("user_id", jwt::claim(userId))
                    .set_issued_at(std::chrono::system_clock::now())
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(1))
                    .sign(jwt::algorithm::hs256{secretKey});

    return token;
}