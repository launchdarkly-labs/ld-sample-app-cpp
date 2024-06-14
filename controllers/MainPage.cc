#include "MainPage.h"
#include "../LDClient.h"

void MainPage::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto response = HttpResponse::newHttpResponse();
    LDClient *client = LDClient::getInstance();
    response->setStatusCode(k200OK);
    response->setContentTypeCode(CT_TEXT_HTML);
    response->setBody("<p>Hello, World!</p>");
    callback(response);
}
