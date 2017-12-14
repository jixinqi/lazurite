#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "lazurite_core.h"

int main()
{
	lazurite::http::server http_server;
	http_server.run();
}