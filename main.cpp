#include <drogon/drogon.h>
#include "src/repository/UserRepository.h"
#include "src/controller/ProfileController.h"

int main() {
    // drogon::app().registerHandler("/", [](const drogon::HttpRequestPtr &req,
    //                                       std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    //     auto resp = drogon::HttpResponse::newHttpResponse();
    //     resp->setBody("Hello, World!");
    //     resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    //     callback(resp);
    // });

    // auto dbClient = drogon::app().getDbClient();
    // UserRepository userRepo(dbClient);
    // auto &controller = drogon::app().registerController(std::make_shared<ProfileController>(userRepo));

    // drogon::app().setLogLevel(trantor::Logger::kError);
    // drogon::app().addListener("127.0.0.1", 8080);
    drogon::app().loadConfigFile("config/config.json");
    drogon::app().run();
    
    return 0;
}
