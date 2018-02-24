#include "lazurite_header.h"

void lazurite::http::response_build::status_code(std::uint16_t _status_code)
{
    _response.status_code = _status_code;
}

void lazurite::http::response_build::phrase(std::string _phrase)
{
    _response.phrase = _phrase;
}

void lazurite::http::response_build::msg_body(std::string _msg_body)
{
    _response.msg_body = _msg_body;
}


void lazurite::http::response_build::error_msg_body()
{
    _response.msg_body.clear();
    _response.msg_body.append(std::to_string(_response.status_code))
                      .append(" ")
                      .append(_response.phrase);
}


std::uint16_t lazurite::http::response_build::status_code()
{
    return _response.status_code;
}

std::string lazurite::http::response_build::phrase()
{
    return _response.phrase;
}

std::string lazurite::http::response_build::msg_body()
{
    return _response.msg_body;
}

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
