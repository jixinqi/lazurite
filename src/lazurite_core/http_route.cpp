#include "lazurite_header.h"

void lazurite::http::route::add_route
(
    std::string &path,
    std::function<std::string(request&, response&)> handle
)
{
    route_table.insert({ path,handle });
}

void lazurite::http::route::build_error_response_msg_body(response &_response)
{
    _response.msg_body.append(std::to_string(_response.status_code))
                      .append(" ")
                      .append(_response.phrase);
}

void lazurite::http::route::run_route_handle(request &_request, response &_response)
{
    std::string path = _request.request_uri;
    auto it = route_table.find(path);
    if (it == route_table.end())
    {
        _response.status_code = 404;
        _response.phrase = "Not Found";
        build_error_response_msg_body(_response);
    }
    else
    {
        _response.msg_body = route_table[path](_request, _response);
    }
}