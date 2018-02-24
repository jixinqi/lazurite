#ifndef _LAZURITE_HTTP_REQUEST_H_
#define _LAZURITE_HTTP_REQUEST_H_

namespace lazurite
{
    namespace http
    {
        class request
        {
        public:
            void                               append_raw_msg(std::string &msg);

            void                               add_params(std::string &key, std::string &value);
            void                               add_header(std::string &key, std::string &value);

            void                               request_method(std::string &method);
            void                               request_uri(std::string &uri);
            void                               request_version(std::string &version);

            std::string                        raw_msg();
            std::string                        request_method();
            std::string                        request_uri();
            std::string                        request_version();
            std::map<std::string, std::string> params();
            std::map<std::string, std::string> header();

            void                               first_line_end_index(std::size_t index);
            void                               header_end_index(std::size_t index);
            void                               body_end_index(std::size_t index);

            std::size_t                        first_line_end_index();
            std::size_t                        header_end_index();
            std::size_t                        body_end_index();

        private:
            std::size_t _first_line_end_index = 0;
            std::size_t _header_end_index     = 0;
            std::size_t _body_end_index       = 0;

            std::string _raw_msg;

            std::string _request_method;
            std::string _request_uri;
            std::string _request_version;
            std::map<std::string, std::string> _params;
            std::map<std::string, std::string> _header;
            std::map<std::string, std::string> _data;
        };

        class request_parser
        {
        public:
            request_parser() = default;

            void          append_msg(const http_msg_buffer &_http_msg_buffer, const std::size_t &_length);
            bool          do_parse();
            bool          msg_end();

            request&      get_request();

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
