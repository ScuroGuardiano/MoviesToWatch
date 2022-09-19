#include "hello_controller.hpp"
#include <iostream>
#include "database.hpp"

using namespace drogon;

Task<> api::Hello::hello(
  const HttpRequestPtr req,
  std::function<void (const HttpResponsePtr &)> callback
) {
  Json::Value json;
  json["message"] = "Hello, world!";

  auto result = co_await queryDatabase("SELECT * FROM misie;");
  if (result)
  {
    std::cout << "Result from DB: " << result.value()->getResults()[0].getTime() << std::endl;
  }
  else
  {
    std::cout << "Error on DB: " << result.error()->getStatusCode() << std::endl;
    std::cout << result.error()->getDescription() << std::endl;
    std::cout << result.error()->getDetails() << std::endl;
    std::cout << result.error()->getInformation() << std::endl;
  }

  callback(HttpResponse::newHttpJsonResponse(json));
  co_return;
}
