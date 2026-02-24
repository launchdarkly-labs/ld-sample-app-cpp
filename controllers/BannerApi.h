#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class BannerApi : public drogon::HttpSimpleController<BannerApi>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/api/banner", Get);
    PATH_LIST_END
};
