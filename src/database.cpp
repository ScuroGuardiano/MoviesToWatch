#include "database.hpp"
#include "lib/base64.hpp"

using namespace drogon;

Task<std::expected<
        std::shared_ptr<SurrealSuccessResponse>,
        std::shared_ptr<SurrealErrorResponse>>>
queryDatabase(std::string query)
{
  auto httpClient = HttpClient::newHttpClient("http://localhost:8000");
  auto req = HttpRequest::newHttpRequest();
  req->setMethod(HttpMethod::Post);
  req->setPath("/sql");
  req->addHeader("NS", "movies_to_watch");
  req->addHeader("DB", "movies_to_watch");
  req->setContentTypeString("application/json");
  req->addHeader("Authorization", "Basic " + macaron::Base64::Encode("root:root"));
  req->setBody(query);

  auto resp = co_await httpClient->sendRequestCoro(req);
  uint status = resp->getStatusCode();
  std::shared_ptr<Json::Value> parsedBody = resp->getJsonObject();

  if (status >= 200 && status <= 299)
  {
    // Success
    co_return std::make_shared<SurrealSuccessResponse>(parsedBody, status);
  }
  else
  {
    // Error
    co_return std::unexpected(std::make_shared<SurrealErrorResponse>(parsedBody, status));
  }
}

SurrealResponse::SurrealResponse(uint code, bool success)
  : code(code), success(success)
{
}

uint SurrealResponse::getStatusCode()
{
  return code;
}

bool SurrealResponse::isSuccess()
{
  return success;
}

SurrealSuccessResponseResult::SurrealSuccessResponseResult(Json::Value& json)
{
  loadFromJson(json);
}

const std::string& SurrealSuccessResponseResult::getTime() const
{
  return time;
}

const std::string& SurrealSuccessResponseResult::getStatus() const
{
  return status;
}

const Json::Value& SurrealSuccessResponseResult::getResult() const
{
  return result;
}

void SurrealSuccessResponseResult::loadFromJson(Json::Value& json)
{
  if (json["time"].isString())
  {
    time = json["time"].asString();
  }

  if (json["status"].isString())
  {
    status = json["status"].asString();
  }

  result = json["result"];
}

SurrealSuccessResponse::SurrealSuccessResponse(std::shared_ptr<Json::Value> json, uint code)
  : SurrealResponse(code, true)
{
  loadFromJson(*json);
}

const std::vector<SurrealSuccessResponseResult>& SurrealSuccessResponse::getResults() const
{
  return results;
}

void SurrealSuccessResponse::loadFromJson(Json::Value& json)
{
  if (!json.isArray())
  {
    return;
  }

  for (Json::Value& result : json)
  {
    results.push_back(SurrealSuccessResponseResult(result));
  }
}

SurrealErrorResponse::SurrealErrorResponse(std::shared_ptr<Json::Value> json, uint code)
  : SurrealResponse(code, false)
{
  loadFromJson(*json);
}

const std::string& SurrealErrorResponse::getDetails() const
{
  return details;
}
const std::string& SurrealErrorResponse::getDescription() const
{
  return description;
}
const std::string& SurrealErrorResponse::getInformation() const
{
  return information;
}

void SurrealErrorResponse::loadFromJson(Json::Value& json) {
  if (json["details"].isString())
  {
    details = json["details"].asString();
  }

  if (json["description"].isString())
  {
    description = json["description"].asString();
  }

  if (json["information"].isString())
  {
    information = json["information"].asString();
  }
}
