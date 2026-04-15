/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#include "Client.hpp"

#include <chrono>
#include <memory>

namespace my_teams::client {

Client::Client(const int &port, const std::string &ipAddress): _socket{
    _ioContext}
{
    network::Endpoint endPoint{port, ipAddress};
    _socket.connect(endPoint);
    _buffer.resize(1024);
}

void Client::send(const std::string &message,
    const network::ConnectedSocket::Callback &handler) const
{
    _socket.write(network::buffer(message + "\r\n"), handler);
}

std::string Client::receive()
{
    _transmission.clear();

    while (!_transmission.ends_with("\r\n")) {
        _socket.read(network::buffer(_buffer, _buffer.size()),
            [this](const std::error_code &, const std::size_t bytes) {
                _transmission.insert(_transmission.end(), _buffer.begin(),
                    _buffer.begin() + bytes);
            });
    }

    if (_transmission.ends_with("\r\n")) {
        _transmission.pop_back();
        _transmission.pop_back();
    }

    return _transmission;
}

} // my_teams
