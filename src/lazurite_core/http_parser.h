#ifndef _LAZURITE_HTTP_PARSER_H_
#define _LAZURITE_HTTP_PARSER_H_

namespace lazurite
{
    namespace http
    {
        struct request
        {
            std::size_t first_line_end_index = 0;
            std::size_t header_end_index     = 0;
            std::size_t body_end_index       = 0;

            std::string raw_request_msg;

            std::string request_method;
            std::string request_uri;
            std::string request_version;
            std::map<std::string, std::string> params;
            std::map<std::string, std::string> header;
            std::map<std::string, std::string> data;
        };

        class parser
        {
        public:
            parser();
            std::size_t   raw_msg_length();
            void          append_msg(const http_msg_buffer &_http_msg_buffer, const std::size_t &_length);

            bool          do_parse();
            bool          msg_end();

        private:
            request       _request;
            bool          parser_first_line();
            bool          parser_uri();
            bool          parser_header();
            bool          parser_body();
        };
    }
}

#endif
