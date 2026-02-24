#include "IndexPage.h"
#include "../LDClient.h"
#include <drogon/HttpResponse.h>
#include <cstdlib>
#include <cstring>

using namespace drogon;
using namespace launchdarkly;
using namespace launchdarkly::server_side;

static Context buildContext()
{
    return ContextBuilder()
        .Kind("user", "user-018e7bd4-ab96-782e-87b0-b1e32082b481")
        .Name("Miriam Wilson")
        .Set("language", "en")
        .Set("tier", "premium")
        .Set("userId", "mwilson")
        .Set("role", "developer")
        .Set("email", "miriam.wilson@example.com")
        .Kind("device", "device-018e7bd4-ab96-782e-87b0-b1e32082b481")
        .Set("os", "macOS")
        .Set("osVersion", "15.6")
        .Set("model", "MacBook Pro")
        .Set("manufacturer", "Apple")
        .Build();
}

void MainPage::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                      std::function<void(const HttpResponsePtr &)> &&callback)
{
    LDClient *ldclient = LDClient::getInstance();
    Client &client = ldclient->client;
    auto const context = buildContext();

    bool homePageSlider = client.BoolVariation(context, "release-home-page-slider", false);
    bool coffeePromo1 = client.BoolVariation(context, "coffee-promo-1", false);
    bool coffeePromo2 = client.BoolVariation(context, "coffee-promo-2", false);

    const char *clientKey = std::getenv("LD_CLIENT_KEY");
    std::string clientKeyStr = clientKey && strlen(clientKey) ? clientKey : "";

    HttpViewData data;
    data.insert("title", std::string("Home"));
    data.insert("clientKey", clientKeyStr);
    data.insert("currentPath", req->path());
    data.insert("homePageSlider", homePageSlider);
    data.insert("coffeePromo1", coffeePromo1);
    data.insert("coffeePromo2", coffeePromo2);

    auto resp = HttpResponse::newHttpViewResponse("IndexView", data);
    callback(resp);
}
