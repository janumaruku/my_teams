/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#include "Client.hpp"

namespace my_teams::client {

Client::Client(const int &port, const std::string &ipAddress): _socket {
    _ioContext}
{
    network::Endpoint endPoint{port, ipAddress};
    _socket.connect(endPoint);
}

void Client::start()
{
    handleWrite();

    _ioContext.run();
}

void Client::handleWrite()
{
    const std::string message = "One love";
    // message += "\r\n";
    _socket.asyncWrite(network::buffer(message),
        [this](const std::error_code &err, auto) {
            if (err) {
                std::cerr << err.message() << std::endl;
                handleWrite();
            } else {
                std::cout << "Message sent successfully" << std::endl;
                handleRead();
            }
        });
}

void Client::handleRead()
{
    _buffer.resize(1024);

    _socket.asyncReadSome(network::buffer(_buffer, _buffer.size()),
        [this](const std::error_code &err, const std::size_t bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                handleRead();
            } else {
                _buffer.resize(bytes);
                std::cout << "Received from server:" << std::endl;
                std::cout << _buffer << std::endl;
                handleWrite();
            }
        });
}
} // my_teams
