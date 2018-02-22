#ifndef _LAZURITE_HTTP_RESPONSE_H_
#define _LAZURITE_HTTP_PESPONSE_H_

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
            void set_status(std::uint16_t status_code,std::string response_phrase);
            void response_msg_body();
            std::string build_response_msg();

            response                 _response;
        private:
            std::shared_ptr<request> request_ptr;
        };
    }
}
#endif