#include <drogon/drogon.h>

int main() {
    drogon::app().registerHandler("/", [](const drogon::HttpRequestPtr &req,
                                          std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setBody("Hello, World!");
        resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
        callback(resp);
    });

    drogon::app().addListener("127.0.0.1", 8080);
    drogon::app().run();
    
    return 0;
}
