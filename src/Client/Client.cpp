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
    _ioContext}, _context{UNDEFINED}
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

void Client::setContext(const CommandContextType &newContext) noexcept
{
    _context = newContext;
}


const std::string &Client::getUserId() const noexcept
{
    return _userId;
}

void Client::setUserId(std::string &uuid) noexcept
{
    _userId = uuid;    
}

const std::string &Client::getTeamId() const noexcept
{
    return _teamId;
}

void Client::setTeamId(std::string &uuid) noexcept
{
    _teamId = uuid;
}

void Client::setThreadId(std::string &uuid) noexcept
{
    _threadId = uuid;
}

const std::string &Client::getChannelId() const noexcept
{
    return _channelId;
}

void Client::setChannelId(std::string &uuid) noexcept
{
    _channelId = uuid;
}

const std::string &Client::getThreadId() const noexcept
{
    return _threadId;
}

CommandContextType Client::getContext() const noexcept
{
    return _context;
}
} // my_teams
