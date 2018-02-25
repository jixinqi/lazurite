#include "lazurite_header.h"

void lazurite::http::route::add
(
    std::string path,
    std::function<void(request&, response&)> handle
)
{
    route_table.insert({ path,handle });
}

void lazurite::http::route::run_handle(request &_request, response &_response)
{
    std::string path = _request.request_uri();
    auto it = route_table.find(path);
    if (it == route_table.end())
    {
        _response.status_code(404);
        _response.phrase("Not Found");
        _response.error_msg_body();
    }
    else
    {
        route_table[path](_request, _response);
    }
}