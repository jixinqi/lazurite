#ifndef _LAZURITE_HTTP_RESPONSE_H_
#define _LAZURITE_HTTP_RESPONSE_H_

namespace lazurite
{
    namespace http
    {
        struct response
        {
            std::uint16_t status_code = 0;
            std::string   phrase;
            std::string   msg_body;
        };

        class response_build
        {
        public:
            response_build() = default;

            void status_code(std::uint16_t code);
            void phrase(std::string _phrase);
            void msg_body(std::string _msg_body);
            void error_msg_body();

            std::uint16_t status_code();
            std::string   phrase();
            std::string   msg_body();

            std::string   build_response_msg();

        private:
            response                 _response;
            
            std::shared_ptr<request> request_ptr;
        };
    }
}
#endif
