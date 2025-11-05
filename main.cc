#include <launchdarkly/context_builder.hpp>
#include <launchdarkly/server_side/client.hpp>
#include <launchdarkly/server_side/config/config_builder.hpp>
#include <drogon/drogon.h>
#include "LDClient.h"

#include <cstring>
#include <iostream>

#define FEATURE_FLAG_KEY "test-flag"

using namespace drogon;
using namespace launchdarkly;
using namespace launchdarkly::server_side;

int main()
{
    LDClient *ldclient = LDClient::getInstance();
    Client &client = ldclient->client;

    auto const context = ContextBuilder().Kind("user", "example-user-key").Name("Sandy").Build();
    client.Identify(context);
    bool showFeature = client.BoolVariation(context, FEATURE_FLAG_KEY, false);

    app().registerHandler(
        "/",
        [showFeature](const HttpRequestPtr &request,
            std::function<void(const HttpResponsePtr &)> &&callback) {
                LOG_INFO << "connected:"
                        << (request->connected() ? "true" : "false");
                auto resp = HttpResponse::newHttpResponse();
                if (showFeature) {
                    resp->setBody("Hello, LaunchDarkly!");
                } else {
                    resp->setBody("Hello, World!");
                }
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
