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

			if (!_parser.append_msg(buffer, length))
			{
				return;
			}

			std::size_t parse_index = _parser.get_parse_index();

			if (parse_index == 0)
			{
				if (!_parser.parser_first_line())
				{
					return;
				}
			}
		}
	);
}

void lazurite::http::session::do_write()
{

}