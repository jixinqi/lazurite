#include "lazurite_header.h"

lazurite::http::server::server()
{
}

void lazurite::http::server::add_route()
{
    // dev
}

void lazurite::http::server::run()
{
    std::shared_ptr<boost::asio::io_service> io_service_ptr = std::make_shared<boost::asio::io_service>();
    listen l(io_service_ptr,"0.0.0.0",8000);
    io_service_ptr->run();
}
