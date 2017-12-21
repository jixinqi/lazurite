#ifndef _LAZURITE_HTTP_SESSION_H_
#define _LAZURITE_HTTP_SESSION_H_

namespace lazurite
{
	namespace http
	{
		class session : public std::enable_shared_from_this<session>
		{
		public:
			session(
				std::shared_ptr<boost::asio::io_service> io_service_ptr,
				boost::asio::ip::tcp::socket             socket
			);
			session& operator=(const session &) = delete;
			void start();
			void do_read();
			void do_write();
		private:
			std::shared_ptr<boost::asio::io_service> io_service_ptr;
			boost::asio::ip::tcp::socket             socket;
			
			std::array<unsigned char, 8 * 1024>      buffer;
		};
	}
}

#endif