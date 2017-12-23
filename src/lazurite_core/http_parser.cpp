#include "lazurite_header.h"

lazurite::http::parser::parser()
{
}

bool lazurite::http::parser::append_msg(const http_msg_buffer &_http_msg_buffer, const std::size_t &_length)
{
    if (_request.raw_http_request_msg.size() + _length > 64 * 1024 * 1024)
    {
        return false;
    }
    for (std::size_t i = 0; i != _length; i++)
    {
        _request.raw_http_request_msg.push_back(_http_msg_buffer.at(i));
    }
    return true;
}

std::size_t lazurite::http::parser::get_parse_index()
{
    return _request.parse_status;
}

void lazurite::http::parser::set_parse_index(const std::size_t &index)
{
    _request.parse_status = index;
}

bool lazurite::http::parser::parser_first_line()
{
    std::size_t index = _request.raw_http_request_msg.find("\r\n");
    if (index == _request.raw_http_request_msg.npos)
    {
        return false;
    }

    std::vector<std::string> items;
    std::string temp = "";
    std::size_t i = _request.parse_index;
    for (; i != index; i++)
    {
        if (_request.raw_http_request_msg.at(i) != ' ')
        {
            temp.push_back(_request.raw_http_request_msg.at(i));
        }
        else
        {
            items.push_back(temp);
            temp.clear();
        }
    }
    items.push_back(temp);

    if (items.size() != 3)
    {
        return false;
    }

    _request.request_method = items.at(0);
    _request.request_uri = items.at(1);
    _request.request_version = items.at(2);

    _request.parse_index = index;

    return true;
}

bool lazurite::http::parser::get_full_header()
{
    return true;
}