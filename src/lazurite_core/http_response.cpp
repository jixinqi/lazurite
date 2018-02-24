#include "lazurite_header.h"

void lazurite::http::response::status_code(std::uint16_t code)
{
    _status_code = code;
}

void lazurite::http::response::phrase(std::string _phrase)
{
    this->_phrase = _phrase;
}

void lazurite::http::response::msg_body(std::string msg)
{
    _msg_body = msg;
}

std::uint16_t lazurite::http::response::status_code()
{
    return _status_code;
}

std::string lazurite::http::response::phrase()
{
    return _phrase;
}

std::string lazurite::http::response::msg_body()
{
    return _msg_body;
}

void lazurite::http::response::error_msg_body()
{
    _msg_body.clear();
    _msg_body.append(std::to_string(_status_code))
             .append(" ")
             .append(_phrase);
}

std::string lazurite::http::response_build::complete_msg()
{
    std::string result;
    result.append("HTTP/1.1 ")
          .append(std::to_string(_response.status_code()))
          .append(" ")
          .append(_response.phrase())
          .append("\r\n");
    result.append("Connection: close\r\n");
    result.append("Server: lazurite/0.1\r\n");
    result.append("Content-Type: text/plain\r\n");
    result.append("Content-Length: ").append(std::to_string(_response.msg_body().length())).append("\r\n");
    result.append("\r\n");
    result.append(_response.msg_body());
    return result;
}

lazurite::http::response& lazurite::http::response_build::get_response()
{
    return _response;
}