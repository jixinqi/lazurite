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
                std::shared_ptr<route>                   route_ptr,
                boost::asio::ip::tcp::socket             socket
            );
            void start();
            void do_read();
            void do_write();

        private:
            std::shared_ptr<boost::asio::io_service> io_service_ptr;
            std::shared_ptr<route>                   route_ptr;
            boost::asio::ip::tcp::socket             socket;
            http_msg_buffer                          buffer;
            std::string                              http_response_msg;
            request_parser                           _request_parser;
            response_build                           _response_build;
        };
    }
}

#endif
