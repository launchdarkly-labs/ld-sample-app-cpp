#include "BannerApi.h"
#include "../LDClient.h"
#include <drogon/HttpResponse.h>
#include <json/json.h>

using namespace drogon;
using namespace launchdarkly;
using namespace launchdarkly::server_side;

static Context buildContext()
{
    return ContextBuilder()
        .Kind("user", "user-018e7bd4-ab96-782e-87b0-b1e32082b481")
        .Name("Miriam Wilson")
        .Kind("device", "device-018e7bd4-ab96-782e-87b0-b1e32082b481")
        .Build();
}

void BannerApi::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                       std::function<void(const HttpResponsePtr &)> &&callback)
{
    LDClient *ldclient = LDClient::getInstance();
    Client &client = ldclient->client;
    auto const context = buildContext();

    std::string bannerText =
        client.StringVariation(context, "banner-text", "No banner text found!");

    Json::Value json;
    json["primaryBanner"] = bannerText;

    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
