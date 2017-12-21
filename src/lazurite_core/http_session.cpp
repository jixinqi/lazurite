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
			for (std::size_t i = 0; i != length; i++)
			{
				std::cout << buffer.at(i);
			}
			std::cout << std::endl;
		}
	);
}

void lazurite::http::session::do_write()
{

}