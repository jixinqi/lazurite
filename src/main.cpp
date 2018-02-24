#include "lazurite_core.h"

std::string index_page(lazurite::http::request_parser &_request_parser, lazurite::http::response_build &_response_build)
{
    return "index page";
}

std::string about_page(lazurite::http::request_parser &_request_parser, lazurite::http::response_build &_response_build)
{
    return "about page";
}

int main()
{
    lazurite::http::server http_server;
    http_server.add_route("/", index_page);
    http_server.add_route("/about", about_page);
    http_server.run();
}
