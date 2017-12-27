#include "lazurite_header.h"

lazurite::http::parser::parser()
{
}

std::size_t lazurite::http::parser::raw_msg_length()
{
    return _request.raw_request_msg.size();
}

void lazurite::http::parser::append_msg(const http_msg_buffer &_http_msg_buffer, const std::size_t &_length)
{
    for (std::size_t i = 0; i != _length; i++)
    {
        _request.raw_request_msg.push_back(_http_msg_buffer.at(i));
    }
}

bool lazurite::http::parser::do_parse()
{
    if (_request.first_line_end_index == 0)
    {
        if (!parser_first_line())
        {
            return false;
        }
    }
    if (_request.first_line_end_index != 0 && _request.header_end_index == 0)
    {
        /*
        if (!parser_header())
        {
            return false;
        }
        */
    }
    if (_request.header_end_index != 0 && _request.body_end_index == 0)
    {
        /*
        if (!parser_body())
        {
            return false;
        }
        */
    }
    return true;
}

bool lazurite::http::parser::msg_end()
{
    return _request.body_end_index != 0;
}

bool lazurite::http::parser::parser_first_line()
{
    std::size_t index = _request.raw_request_msg.find("\r\n");
    if (index == _request.raw_request_msg.npos)
    {
        return false;
    }
    std::vector<std::string> items;
    std::string temp = "";
    for (std::size_t i = 0; i != index; i++)
    {
        if (_request.raw_request_msg.at(i) != ' ')
        {
            temp.push_back(_request.raw_request_msg.at(i));
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

    _request.request_method       = items.at(0);
    _request.request_uri          = items.at(1);
    _request.request_version      = items.at(2);
    _request.first_line_end_index = index + 2;

    return true;
}

