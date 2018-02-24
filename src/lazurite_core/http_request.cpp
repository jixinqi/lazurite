#include "lazurite_header.h"

void lazurite::http::request::append_raw_msg(std::string &msg)
{
    _raw_msg.append(msg);
}

void lazurite::http::request::add_params(std::string &key, std::string &value)
{
    _params.insert({ key,value });
}

void lazurite::http::request::add_header(std::string &key, std::string &value)
{
    _header.insert({ key,value });
}

void lazurite::http::request::request_method(std::string &method)
{
    _request_method = method;
}

void lazurite::http::request::request_uri(std::string &uri)
{
    _request_uri = uri;
}

void lazurite::http::request::request_version(std::string &version)
{
    _request_version = version;
}

std::string lazurite::http::request::raw_msg()
{
    return _raw_msg;
}

std::string lazurite::http::request::request_method()
{
    return _request_method;
}

std::string lazurite::http::request::request_uri()
{
    return _request_uri;
}

std::string lazurite::http::request::request_version()
{
    return _request_version;
}

std::map<std::string, std::string> lazurite::http::request::params()
{
    return _params;
}

std::map<std::string, std::string> lazurite::http::request::header()
{
    return _header;
}

void lazurite::http::request::first_line_end_index(std::size_t index)
{
    _first_line_end_index = index;
}

void lazurite::http::request::header_end_index(std::size_t index)
{
    _header_end_index = index;
}

void lazurite::http::request::body_end_index(std::size_t index)
{
    _body_end_index = index;
}

std::size_t lazurite::http::request::first_line_end_index()
{
    return _first_line_end_index;
}

std::size_t lazurite::http::request::header_end_index()
{
    return _header_end_index;
}

std::size_t lazurite::http::request::body_end_index()
{
    return _body_end_index;
}

void lazurite::http::request_parser::append_msg(const http_msg_buffer &_http_msg_buffer, const std::size_t &_length)
{
    std::string msg;
    for (std::size_t i = 0; i != _length; i++)
    {
        msg.push_back(_http_msg_buffer.at(i));
    }
    _request.append_raw_msg(msg);
}

bool lazurite::http::request_parser::do_parse()
{
    if (_request.first_line_end_index() == 0)
    {
        if (!parser_first_line())
        {
            return false;
        }
    }
    if (_request.first_line_end_index() != 0 && _request.header_end_index() == 0)
    {
        if (!parser_header())
        {
            return false;
        }
    }
    if (_request.header_end_index() != 0 && _request.body_end_index() == 0)
    {
        if (!parser_body())
        {
            return false;
        }
    }
    return true;
}

bool lazurite::http::request_parser::msg_end()
{
    return _request.body_end_index() != 0;
}

lazurite::http::request& lazurite::http::request_parser::get_request()
{
    return _request;
}

bool lazurite::http::request_parser::parser_first_line()
{
    const std::size_t index = _request.raw_msg().find("\r\n");
    if (index == _request.raw_msg().npos)
    {
        return (_request.raw_msg().length() + 2 <= http_msg_first_line_max_length);
    }
    else if(index + 2 > http_msg_first_line_max_length)
    {
        return false;
    }

    std::vector<std::string> items;
    std::string temp = "";
    for (std::size_t i = 0; i != index; i++)
    {
        if (_request.raw_msg().at(i) != ' ')
        {
            temp.push_back(_request.raw_msg().at(i));
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

    _request.request_method(items.at(0));
    _request.request_uri(items.at(1));
    _request.request_version(items.at(2));
    _request.first_line_end_index(index + 2);

    return true;
}

bool lazurite::http::request_parser::parser_header()
{
    const std::size_t index = _request.raw_msg().find("\r\n\r\n");
    if (index == _request.raw_msg().npos)
    {
        return (_request.raw_msg().length() + 4 - _request.first_line_end_index() <= http_msg_header_max_length);
    }
    else if (index + 4 - _request.first_line_end_index() > http_msg_header_max_length)
    {
        return false;
    }

    std::size_t last_line_break_index = 0;
    std::size_t line_break_index = 0;
    std::string line;
    std::string key;
    std::string value;

    std::string raw_request_header = _request.raw_msg().substr
    (
        _request.first_line_end_index(),
        index - _request.first_line_end_index() + 2
    );

    while (line_break_index != raw_request_header.npos && line_break_index < raw_request_header.length())
    {
        last_line_break_index = line_break_index;
        line_break_index = raw_request_header.find("\r\n", line_break_index);
        line = raw_request_header.substr(last_line_break_index, line_break_index - last_line_break_index);
        line_break_index += 2;

        std::size_t colon_index = line.find(":");
        if (colon_index == line.npos)
        {
            return false;
        }

        key = line.substr(0, colon_index);
        value = line.substr(colon_index + 1, line.length() - 1);
        for (std::size_t erase_space_index = 0; erase_space_index != value.length(); erase_space_index++)
        {
            if (value.at(erase_space_index) != ' ')
            {
                value.erase(0, erase_space_index);
                break;
            }
        }

        _request.add_header(key, value);
    }
    _request.header_end_index(index + 4);

    return true;
}

bool lazurite::http::request_parser::parser_body()
{
    if (_request.request_method() == "GET")
    {
        _request.body_end_index(_request.raw_msg().length());
        return true;
    }
    else
    {
        return false;
    }
}