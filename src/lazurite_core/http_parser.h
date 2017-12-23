#ifndef _LAZURITE_HTTP_PARSER_H_
#define _LAZURITE_HTTP_PARSER_H_

namespace lazurite
{
    namespace http
    {
        struct request
        {
            /*  status:
             *  0   => init
             *  1   => parsed first line
             *  2   => get full header
             *  100 => parsed http header
             *  200 => parsed http body
             *  999 => finish
             */
            std::size_t parse_status = 0;
            std::size_t parse_index = 0;

            std::string raw_http_request_msg;

            std::string request_method;
            std::string request_uri;
            std::string request_version;

            std::string raw_request_header;
            std::string raw_request_body;

            std::map<std::string, std::string> params;
            std::map<std::string, std::string> data;
        };

        class parser
        {
        public:
            parser();
            bool          append_msg(const http_msg_buffer &_http_msg_buffer, const std::size_t &_length);
            std::size_t   get_parse_index();
            void          set_parse_index(const std::size_t &index);

            bool          parser_first_line();
            bool          get_full_header();
            
        private:
            request       _request;
        };
    }
}

#endif