#include "hello_controller.hpp"

using namespace drogon;

void api::Hello::hello(
  const HttpRequestPtr &req,
  std::function<void (const HttpResponsePtr &)> &&callback
) {
  Json::Value json;
  json["message"] = "Hello, world!";
  callback(HttpResponse::newHttpJsonResponse(json));
}
