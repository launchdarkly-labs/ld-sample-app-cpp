#include <drogon/drogon.h>
#include "LDClient.h"

#include <cstring>
#include <iostream>

#define FEATURE_FLAG_KEY "test-flag"

using namespace drogon;

int main()
{
    auto client = *LDClient::getInstance();

    app().registerHandler(
        "/",
        [](const HttpRequestPtr &request,
            std::function<void(const HttpResponsePtr &)> &&callback) {
                LOG_INFO << "connected:"
                        << (request->connected() ? "true" : "false");
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody("Hello, World!");
                callback(resp);
            },
        {Get});
    // Set HTTP listener address and port
    app().addListener("0.0.0.0", 5000);
    // Load config file
    // app().loadConfigFile("../config.json");
    // app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    app().run();
    return 0;
}
