#include "lazurite_header.h"

lazurite::http::session::session(
    std::shared_ptr<boost::asio::io_service> io_service_ptr,
    boost::asio::ip::tcp::socket socket
)
:io_service_ptr(io_service_ptr)
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

            if (!_parser.raw_msg_length() + length > 16 * 1024 * 1024)
            {
                return;
            }

            _parser.append_msg(buffer,length);

            if (!_parser.do_parse())
            {
                do_write_400();
            }

            if (!_parser.msg_end())
            {
                do_read();
            }
            else
            {
                do_write();
            }
        }
    );
}

void lazurite::http::session::do_write()
{
    auto self(shared_from_this());
    
    response_msg.append("HTTP/1.1 200 OK\r\n");
    response_msg.append("Connection: close\r\n");
    response_msg.append("Server: lazurite/0.1\r\n");
    response_msg.append("Content-Type: text/plain\r\n");
    response_msg.append("Content-Length: ").append(std::to_string(_parser.raw_msg_length())).append("\r\n");
    response_msg.append("\r\n");
    response_msg.append(_parser.get_raw_msg());

    boost::asio::async_write(
        socket,
        boost::asio::buffer(response_msg, response_msg.length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (ec)
            {
                return;
            }
        }
    );
}

void lazurite::http::session::do_write_400()
{
    auto self(shared_from_this());
    //dev
}
