#include <iostream>
#include <string>

#include "lazurite_core.h"

std::string hello(lazurite::http::request &_request,lazurite::http::response &_response)
{
    return "hello, world!";
}

std::string about(lazurite::http::request &_request, lazurite::http::response &_response)
{
    return "about page";
}

int main()
{
    lazurite::http::server http_server;
    http_server.add_route("/hello",hello);
    http_server.add_route("/about", about);
    http_server.run();
}
