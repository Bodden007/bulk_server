#pragma once
#include <iostream>
#include <optional>
#include "boost/asio.hpp"
#include "session.hpp"

class server
{
public:
    // FIXME Added inN
    server(boost::asio::io_context &io_context,
           std::uint16_t port, int inN) : io_context(io_context),
                                          acceptor(io_context,
                                                   boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        N = inN;
    }

    void async_accept()
    {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&](boost::system::error_code error)
                              {
                                //FIXME Added N
            std::make_shared<session>(N,io_context,std::move(*socket))->startReading();
            async_accept(); });
    }

private:
    // FIXME Added int N
    int N;
    boost::asio::io_context &io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
};