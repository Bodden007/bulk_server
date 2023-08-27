#include <iostream>
#include <sstream>
#include "boost/asio.hpp"
#include "../server/server.hpp"

/**
 * @brief Entry point to the program
 *
 * @param argc Number of arguments
 * @param argv Arguments: number port, size block bulk
 * @param N Buffer variable
 * @return int 0
 */

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
        std::stringstream strArg;
        strArg << argv[2];
        int N;
        strArg >> N;

        boost::asio::io_context io_context;
        server srv(io_context, 2014);
        srv.async_accept();
        io_context.run();
    }
    else
    {
        std::cout << "Too many arguments" << std::endl;
    }

    return 0;
}
