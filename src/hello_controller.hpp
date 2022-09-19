#pragma once

#include <drogon/HttpController.h>

namespace api {
class Hello : public drogon::HttpController<Hello> {

  public:
    METHOD_LIST_BEGIN
      METHOD_ADD(Hello::hello, "", drogon::Get);
      METHOD_ADD(Hello::hello, "/", drogon::Get);
    METHOD_LIST_END

    drogon::Task<> hello(
      const drogon::HttpRequestPtr req,
      std::function<void (const drogon::HttpResponsePtr &)> callback
    );
};
}
