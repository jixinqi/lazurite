#include "lazurite_header.h"

void lazurite::http::route::add
(
    std::string path,
    std::function<std::string(request_parser&, response_build&)> handle
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

void lazurite::http::route::run_route_handle(request_parser &_request_parser, response_build &_response_build)
{
    std::string path = _request_parser.request_uri();
    auto it = route_table.find(path);
    if (it == route_table.end())
    {
        _response_build.status_code(404);
        _response_build.phrase("Not Found");
        _response_build.error_msg_body();
    }
    else
    {
        _response_build.msg_body(route_table[path](_request_parser, _response_build));
    }
}
