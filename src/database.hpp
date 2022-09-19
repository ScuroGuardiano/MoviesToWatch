#pragma once

#include <drogon/HttpClient.h>
#include <json/json.h>
#include <string>
#include <vector>
#include <expected>

class SurrealResponse
{
public:
  SurrealResponse(uint code, bool success);

  uint getStatusCode();

  bool isSuccess();

protected:
  SurrealResponse() = default;
  uint code;
  bool success;
};

class SurrealSuccessResponseResult
{
public:
  SurrealSuccessResponseResult(Json::Value& json);

  const std::string& getTime() const;
  const std::string& getStatus() const;
  const Json::Value& getResult() const;

private:
  std::string time;
  std::string status;
  Json::Value result;

  void loadFromJson(Json::Value& json);
};

class SurrealSuccessResponse : public SurrealResponse
{
public:
  SurrealSuccessResponse(std::shared_ptr<Json::Value> json, uint code);
  
  const std::vector<SurrealSuccessResponseResult>& getResults() const;

private:
  std::vector<SurrealSuccessResponseResult> results;
  void loadFromJson(Json::Value& json);
};

class SurrealErrorResponse : public SurrealResponse
{
public:
  SurrealErrorResponse(std::shared_ptr<Json::Value> json, uint code);

  const std::string& getDetails() const;
  const std::string& getDescription() const;
  const std::string& getInformation() const;

private:
  std::string details;
  std::string description;
  std::string information;

  void loadFromJson(Json::Value& json);
};

drogon::Task<
    std::expected<
        std::shared_ptr<SurrealSuccessResponse>,
        std::shared_ptr<SurrealErrorResponse>>>
queryDatabase(std::string query);
