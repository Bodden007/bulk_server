#include <iostream>
#include <sstream>
#include "boost/asio.hpp"
#include "../server/server.hpp"
#include <boost/enable_shared_from_this.hpp>
#include "boost/bind/bind.hpp"

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Too few arguments" << std::endl;
    }
    else if (argc == 3)
    {
        std::cout << "Port: " << argv[1] << std::endl;
        std::cout << "Size bulk: " << argv[2] << std::endl;

        std::stringstream portArg;
        portArg << argv[1];
        int port;
        portArg >> port;

        std::stringstream strArg;
        strArg << argv[2];
        int N;
        strArg >> N;

        boost::asio::io_context io_context;
        // FIXME Added 3 - argument
        server srv(io_context, port, N);
        srv.async_accept();
        io_context.run();
    }
    else
    {
        std::cout << "Too many arguments" << std::endl;
    }

    return 0;
}
