#include <launchdarkly/context_builder.hpp>
#include <launchdarkly/server_side/client.hpp>
#include <launchdarkly/server_side/config/config_builder.hpp>
#include <drogon/drogon.h>
#include "LDClient.h"

#include <cstring>
#include <iostream>

#define FEATURE_FLAG_KEY "first-feature"

using namespace drogon;
using namespace launchdarkly;
using namespace launchdarkly::server_side;

int main()
{
    LDClient *ldclient = LDClient::getInstance();
    Client &client = ldclient->client;

    auto const context = ContextBuilder().Kind("user", "example-user-key").Name("Sandy").Build();
    client.Identify(context);

    app().registerHandler(
        "/",
        [=](const HttpRequestPtr &req,
            std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data.insert("name","SuperDude");
            auto resp=HttpResponse::newHttpViewResponse("MainView",data);
            callback(resp);
        },
        {Get});

    app().registerHandler(
        "/main",
        [&client, c_context = context](const HttpRequestPtr &request,
            std::function<void(const HttpResponsePtr &)> &&callback) {
                LOG_INFO << "connected:"
                        << (request->connected() ? "true" : "false");
                auto resp = HttpResponse::newHttpResponse();
                resp->addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
                resp->addHeader("Pragma", "no-cache"); // For backward compatibility with HTTP 1.0
                bool showFeature = client.BoolVariation(c_context, FEATURE_FLAG_KEY, false);
                std::cout << showFeature << std::endl;
                if (showFeature) {
                    resp->setBody("Hello, LaunchDarkly!");
                } else {
                    resp->setBody("Hello, Drogon!");
                }
                callback(resp);
            },
        {Get});
    // Set HTTP listener address and port
    // Load config file
    // app().loadConfigFile("../config.json");
    // app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    app().addListener("0.0.0.0", 5000).run();
    return 0;
}
