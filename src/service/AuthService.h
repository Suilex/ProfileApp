#pragma once

class AuthService {
public:
    std::string generateToken(const std::string &userId);
};