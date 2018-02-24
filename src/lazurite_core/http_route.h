#ifndef _LAZURITE_HTTP_ROUTE_H_
#define _LAZURITE_HTTP_ROUTE_H_

namespace lazurite
{
    namespace http
    {
        /*
        struct binary_tree_route_node
        {
            std::shared_ptr<binary_tree_route_node> left_child;
            std::shared_ptr<binary_tree_route_node> right_child;
            std::string path_item;
            std::function<std::string(lazurite::http::request&, lazurite::http::response&)> handle;
        };
        */

        class route
        {
        public:
            void add
            (
                std::string path,
                std::function<std::string(request_parser&, response_build&)> handle
            );
            void build_error_response_msg_body(response &_response);
            void run_route_handle(request_parser &_request_parser, response_build &_response_build);
        private:
            std::map<std::string,std::function<std::string(request_parser&, response_build&)>> route_table;
        };
    }
}

#endif
