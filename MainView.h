#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class MainView : public drogon::HttpSimpleController<MainView>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/main", Get);
    PATH_LIST_END
};
