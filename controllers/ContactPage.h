#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class ContactPage : public drogon::HttpSimpleController<ContactPage>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/contact", Get);
    PATH_LIST_END
};
