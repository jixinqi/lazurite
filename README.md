# lazurite

Lazurite 是一个基于 BOOST::ASIO 的 HTTP 服务器，可在 Linux 和 Windows 系统上运行。

Lazurite 包含了 Socket I/O 模块，HTTP 数据包 Parser 模块，以及 HTTP 路由模块。

目前该服务器仍然是开发阶段，仅仅支持 GET 请求，可以用做简单的 API 响应。

## 使用实例：

1. 显示 Hello world 页面。

````
// main.cpp

#include "lazurite_core.h"

std::string hello_page(lazurite::http::request &_request, lazurite::http::response &_response)
{
    return "hello_world\n";
}

int main()
{
    lazurite::http::server http_server;
    http_server.add_route("/",hello_page);
    http_server.run();
}
````

编译并运行，用 curl 查看：

````
# curl http://127.0.0.1:8000
hello_world
````

2. 显示原始请求报文页面。

````
std::string raw_msg(lazurite::http::request &_request, lazurite::http::response &_response)
{
    return _request.raw_msg();
}

http_server.add_route("/raw_msg",raw_msg);
````

运行结果：

````
# curl http://127.0.0.1:8000/raw_msg
GET /raw_msg HTTP/1.1
Host: 127.0.0.1:8000
User-Agent: curl/7.29.0
Accept: */*
Connection: keep-alive
````

3. 响应 404。

任何未添加 route 的 uri 都会响应 404

````
# curl http://127.0.0.1:8000/a
404 Not Found
````
