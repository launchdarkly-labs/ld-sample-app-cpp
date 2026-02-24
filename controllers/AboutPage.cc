#include "AboutPage.h"
#include <drogon/HttpResponse.h>
#include <cstdlib>
#include <cstring>

using namespace drogon;

void AboutPage::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                       std::function<void(const HttpResponsePtr &)> &&callback)
{
    const char *clientKey = std::getenv("LD_CLIENT_KEY");
    std::string clientKeyStr = clientKey && strlen(clientKey) ? clientKey : "";

    HttpViewData data;
    data.insert("title", std::string("About"));
    data.insert("clientKey", clientKeyStr);
    data.insert("currentPath", req->path());

    auto resp = HttpResponse::newHttpViewResponse("AboutView", data);
    callback(resp);
}
