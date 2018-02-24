#include "lazurite_core.h"

std::string index_page(lazurite::http::request &_request, lazurite::http::response &_response)
{
    return "index page";
}

std::string about_page(lazurite::http::request &_request, lazurite::http::response &_response)
{
    return "about page";
}

int main()
{
    lazurite::http::server http_server;
    http_server.add_route("/",      index_page);
    http_server.add_route("/about", about_page);
    http_server.run();
}
