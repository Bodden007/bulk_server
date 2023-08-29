#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include "boost/asio.hpp"
#include <boost/algorithm/string/trim_all.hpp>
#include "classTest.hpp"

class session : public std::enable_shared_from_this<session>
{
    // FIXME Class control to need create
    //  classTest clTest;

public:
    session(boost::asio::io_context &io_context,
            boost::asio::ip::tcp::socket &&socket) : io_context(io_context),
                                                     socket(std::move(socket))
    {
    }
    // TODO Need to will off io_context
    void startReading()
    {
        auto self(shared_from_this());
        boost::asio::async_read_until(
            socket,
            streambuf,
            '\n',
            [self, this](
                const boost::system::error_code error,
                const std::size_t length)
            {
                // TODO off io_context

                // std::istream is(&self->streambuf);
                // std::string line;
                // std::getline(is, line);
                // std::cout << "line: " << line << std::endl;
                // if (line.compare("stop") == 0)
                // {
                //     self->io_context.stop();
                // }
                handleRead(error, length);
            });
    }

    // FIXME method to need delete
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
    void handleRead(const boost::system::error_code error,
                    const std::size_t length)
    {
        if (error)
        {
            std::cout << std::this_thread::get_id() << " Client \""
                      << "\": Reading error: \"" << error << "\"." << std::endl;
            return;
        }
        if (length != 0)
        {
            handleData(length);
            streambuf.consume(length);
        }
        startReading();
    }

    void handleData(const std::size_t length)
    {

        std::string name{boost::asio::buffer_cast<const char *>(streambuf.data()),
                         length};
        boost::trim(name);
        std::cout << "Test: " << name << std::endl;

        connect(name);
    }

    boost::asio::io_context &io_context;
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<std::string> vec;
};