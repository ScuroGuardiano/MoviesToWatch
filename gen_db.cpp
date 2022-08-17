#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <drogon/orm/DbClient.h>
#include <json/json.h>
#include <boost/algorithm/string/trim.hpp>

struct DatabaseConfig {
  std::string host;
  int port;
  std::string username;
  std::string password;
  std::string database;
  std::vector<std::string> queriesToRun;
};

void readingConfigError(std::string message) {
  std::cout << "Error while reading config: " << message << std::endl;
  exit(1);
}

template <typename T>
T getCfgValFromJson(const Json::Value& config, std::string key) {
  Json::Value value = config[key];

  if (value.is<T>()) {
    return value.as<T>();
  }

  if (value.isNull()) {
    readingConfigError("\"" + key + "\" is required.");
  } else {
    readingConfigError("\"" + key + "\" has invalid type");
  }
}

template <typename T>
T getCfgValFromJson(const Json::Value& config, std::string key, T defaultValue) {
  Json::Value value = config.get(key, defaultValue);
  
  if (value.is<T>()) {
    return value.as<T>();
  }

  readingConfigError("\"" + key + "\" has invalid type");
}

std::string getPath() {
  std::string path;  
  bool pathCorrect = false;

  while (!pathCorrect) {
    std::cout << "HINT: Current path is " << std::filesystem::current_path() << std::endl;
    std::cout << "Enter path to your database gen config> ";
    std::getline(std::cin, path);
    boost::trim(path);
    if (path.empty()) {
      std::cout << "Path cannot be empty!" << std::endl;
    }
    else if (!std::filesystem::exists(path)) {
      std::cout << "File " << std::filesystem::absolute(path) << " does not exists!" << std::endl;
    }
    else {
      pathCorrect = true;
    }
  }

  return path;
}

DatabaseConfig readConfig(const std::string& path) {
  std::cout << "Opening config file: " << std::filesystem::absolute(path) << "..." << std::endl;
  std::ifstream configFStream(path);
  
  if (!configFStream.is_open()) {
    std::cout << "Couldn't open the file." << std::endl;
    exit(1);
  }

  std::cout << "Parsing config..." << std::endl;
  Json::Reader reader;
  Json::Value parsed;

  bool result = reader.parse(configFStream, parsed);
  if (!result) {
    std::cout << "Couldn't parse JSON, sowwi memowwi" << std::endl;
    exit(1);
  }

  DatabaseConfig config;

  config.host = getCfgValFromJson<std::string>(parsed, "host", "localhost");
  config.port = getCfgValFromJson<int>(parsed, "port", 5432);
  config.username = getCfgValFromJson<std::string>(parsed, "username");
  config.password = getCfgValFromJson<std::string>(parsed, "password", "");
  config.database = getCfgValFromJson<std::string>(parsed, "database");

  // Cool now have only load this fucking array god kill me plz
  
  if (!parsed["queriesToRun"].isNull() && parsed["queriesToRun"].isArray()) {
    for (const auto& val : parsed["queriesToRun"]) {
      if (val.isString()) {
        config.queriesToRun.push_back(val.asString());
      } else {
        readingConfigError("Fuck you, queriesToRun must be string array only. JESUS!");
      }
    }
  } else {
    readingConfigError("Fuck you, queriesToRun must be string array only. JESUS!");
  }

  std::cout << "Parsing config done..." << std::endl;

  return config;
}

int main(int argc, char** argv) {
  std::cout << "Scuro Guardiano's DB generator." << std::endl << std::endl;

  auto path = getPath();
  DatabaseConfig config = readConfig(path);
  std::cout << "Using database: " << "pg://" << config.host << ":" << config.port << "/" << config.database << std::endl;
}
