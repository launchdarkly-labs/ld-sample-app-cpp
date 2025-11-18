#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include "MainView.h"

using namespace drogon;

void MainView::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    HttpViewData data;
    data["name"] = "LaunchDarkly";
    auto resp = HttpResponse::newHttpViewResponse("MainView.csp", data);
    callback(resp);
}
