#pragma once

#include <crow.h>

namespace wims
{
class WimServer
{
  public:
    WimServer(const std::string& address, const uint16_t port);

    void start();

    crow::SimpleApp& application();

  private:
    crow::SimpleApp application_;
    std::string ip_address_;
    uint16_t port_;
};

WimServer::WimServer(const std::string& address, const uint16_t port) : ip_address_(address), port_(port)
{
};

void WimServer::start()
{
    //set the port, set the app to run on multiple threads, and run the app
    application_.bindaddr(ip_address_).port(port_).loglevel(crow::LogLevel::WARNING).multithreaded().run();
};

crow::SimpleApp& WimServer::application()
{
  return application_;
};

}  // namespace wims
