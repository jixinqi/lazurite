#ifndef _LAZURITE_HEADER_H_
#define _LAZURITE_HEADER_H_

#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <fstream>

#include <boost/asio.hpp>

/*
namespace lazurite
{
    namespace http
    {
        typedef std::array<unsigned char, 4 * 1024> http_msg_buffer;
    }
}
*/

#include "lazurite_config.h"
#include "http_parser.h"
#include "http_listen.h"
#include "http_server.h"
#include "http_session.h"

#endif
