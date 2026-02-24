#include "ProductsPage.h"
#include <drogon/HttpResponse.h>
#include <cstdlib>
#include <cstring>

using namespace drogon;

void ProductsPage::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                          std::function<void(const HttpResponsePtr &)> &&callback)
{
    const char *clientKey = std::getenv("LD_CLIENT_KEY");
    std::string clientKeyStr = clientKey && strlen(clientKey) ? clientKey : "";

    HttpViewData data;
    data.insert("title", std::string("Products"));
    data.insert("clientKey", clientKeyStr);
    data.insert("currentPath", req->path());

    auto resp = HttpResponse::newHttpViewResponse("ProductsView", data);
    callback(resp);
}
