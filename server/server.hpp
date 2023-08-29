#pragma once
#include <iostream>
#include <optional>
#include "boost/asio.hpp"
#include "session.hpp"

class server
{
public:
    server(boost::asio::io_context &io_context,
           std::uint16_t port) : io_context(io_context),
                                 acceptor(io_context,
                                          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

    void async_accept()
    {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&](boost::system::error_code error)
                              {
            std::make_shared<session>(io_context,std::move(*socket))->startReading();
            async_accept(); });
    }

private:
    boost::asio::io_context &io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
};