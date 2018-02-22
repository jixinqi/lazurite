#include "lazurite_header.h"

lazurite::http::server::server()
{
}

void lazurite::http::server::add_route(
    std::string path,
    std::function<std::string(request&, response&)> handle
)
{
    route_ptr->add_route(path,handle);
}

void lazurite::http::server::run()
{
    std::shared_ptr<boost::asio::io_service> io_service_ptr = std::make_shared<boost::asio::io_service>();
    listen l(io_service_ptr, route_ptr, "0.0.0.0", server_listen_port);
    io_service_ptr->run();
}
