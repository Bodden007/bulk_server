#pragma once
#include <iostream>
#include <vector>
#include "boost/asio.hpp"
#include "classTest.hpp"

class session : public std::enable_shared_from_this<session>
{
    classTest clTest;

public:
    session(boost::asio::io_context &io_context,
            boost::asio::ip::tcp::socket &&socket) : io_context(io_context),
                                                     socket(std::move(socket))
    {
    }

    void start()
    {
        boost::asio::async_read_until(
            socket,
            streambuf,
            '\n',
            [self = shared_from_this(), this](
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

                connect(line);
            });
    }

    void connect(std::string val)
    {
        vec.push_back(val);
        if (val.compare("all") == 0)
        {
            std::cout << "Vector size:  " << vec.size() << std::endl;
            for (auto v : vec)
            {
                std::cout << "Vector: " << v << std::endl;
            }
        }
    }

private:
    boost::asio::io_context &io_context;
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> vec;
};