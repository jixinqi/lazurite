#ifndef _LAZURITE_HTTP_SERVER_H_
#define _LAZURITE_HTTP_SERVER_H_

namespace lazurite
{
    namespace http
    {
        class server
        {
        public:
            server();
            server& operator=(const server &) = delete;
            void add_route();
            void run();
        private:
        };
    }
}

#endif
