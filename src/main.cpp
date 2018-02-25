#include "lazurite_core.h"

void hello_page(lazurite::http::request &_request, lazurite::http::response &_response)
{
    _response.msg_body("hello_world\n");
}

void raw_msg(lazurite::http::request &_request, lazurite::http::response &_response)
{
    _response.msg_body(_request.raw_msg());
}

int main()
{
    lazurite::http::server http_server;
    http_server.add_route("/", hello_page);
    http_server.add_route("/raw_msg", raw_msg);
    http_server.run();
}