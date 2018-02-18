#ifndef _LAZURITE_CONFIG_H_
#define _LAZURITE_CONFIG_H_

const std::size_t http_msg_buffer_length         = 4  * 1024;
//const std::size_t http_msg_buffer_length         = 4;
const std::size_t http_msg_first_line_max_length = 8  * 1024;
const std::size_t http_msg_header_max_length     = 16 * 1024;
const std::size_t http_msg_body_max_length       = 16 * 1024 * 1024;

namespace lazurite
{
    namespace http
    {
        typedef std::array<unsigned char, http_msg_buffer_length> http_msg_buffer;
    }
}

#endif
