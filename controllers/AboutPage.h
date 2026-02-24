#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class AboutPage : public drogon::HttpSimpleController<AboutPage>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/about", Get);
    PATH_LIST_END
};
