#include <iostream>
#include "src/hello_controller.hpp"
#include <drogon/drogon.h>

int main() {
  using drogon::app;

  app()
    .addListener("0.0.0.0", 1337)
    .registerBeginningAdvice([]() {
        if (app().getListeners().size() == 0) {
            return;
        }
        LOG_INFO << "The app is listening on "<< app().getListeners().front().toIpPort();
    })
    .setThreadNum(0)
    .setLogPath("")
    .setLogLevel(trantor::Logger::LogLevel::kDebug)
    .run();
}
