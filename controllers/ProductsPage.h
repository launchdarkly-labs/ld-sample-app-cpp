#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class ProductsPage : public drogon::HttpSimpleController<ProductsPage>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/products", Get);
    PATH_LIST_END
};
