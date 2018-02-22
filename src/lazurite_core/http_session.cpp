#include "lazurite_header.h"

lazurite::http::session::session(
    std::shared_ptr<boost::asio::io_service> io_service_ptr,
    std::shared_ptr<route>                   route_ptr,
    boost::asio::ip::tcp::socket             socket
)
:io_service_ptr(io_service_ptr)
,route_ptr(route_ptr)
,socket(std::move(socket))
{
}

void lazurite::http::session::start()
{
    do_read();
}

void lazurite::http::session::do_read()
{
    auto self(shared_from_this());
    socket.async_read_some(
        boost::asio::buffer(buffer),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (ec)
            {
                return;
            }

            _request_parser.append_msg(buffer,length);

            if (!_request_parser.do_parse())
            {
                return;
            }

            if (!_request_parser.msg_end())
            {
                do_read();
            }
            else
            {
                //response_msg_body();
                do_write();
            }
        }
    );
}

void lazurite::http::session::do_write()
{
    auto self(shared_from_this());
    //http_response_msg = _response_build.build_response_msg();
    route_ptr->run_route_handle(_request_parser._request,_response_build._response);
    http_response_msg = _response_build.build_response_msg();
    boost::asio::async_write(
        socket,
        boost::asio::buffer(http_response_msg, http_response_msg.length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (ec)
            {
                return;
            }
        }
    );
}
