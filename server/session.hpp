#pragma once
#include <iostream>
#include "boost/asio.hpp"

class session : public std::enable_shared_from_this<session>
{
public:
    session(boost::asio::io_context &io_context,
            boost::asio::ip::tcp::socket &&socket) : io_context(io_context),
                                                     socket(std::move(socket)) {}

    void start()
    {
        boost::asio::async_read_until(
            socket,
            streambuf,
            '\n',
            [self = shared_from_this()](
                boost::system::error_code error,
                std::size_t bytes_transferred)
            {
                std::istream is(&self->streambuf);
                std::string line;
                std::getline(is, line);
                std::cout << "line: " << line << std::endl;
                if (line.compare("stop") == 0)
                {
                    self->io_context.stop();
                }
            });
    }

private:
    boost::asio::io_context &io_context;
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
};