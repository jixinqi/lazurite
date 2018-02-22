#include "lazurite_header.h"

/*
void lazurite::http::response_build::set_status(std::uint16_t status_code, std::string response_phrase)
{
    _response.status_code = status_code;
    _response.phrase      = response_phrase;
}

void lazurite::http::response_build::response_msg_body()
{
    if (_response.status_code != 0)
    {
        _response.msg_body.append(std::to_string(_response.status_code))
                          .append(" ")
                          .append(_response.phrase);
    }
}
*/

std::string lazurite::http::response_build::build_response_msg()
{
    std::string result;
    result.append("HTTP/1.1 ")
          .append(std::to_string(_response.status_code))
          .append(" ")
          .append(_response.phrase)
          .append("\r\n");
    result.append("Connection: close\r\n");
    result.append("Server: lazurite/0.1\r\n");
    result.append("Content-Type: text/plain\r\n");
    result.append("Content-Length: ").append(std::to_string(_response.msg_body.length())).append("\r\n");
    result.append("\r\n");
    result.append(_response.msg_body);
    return result;
}