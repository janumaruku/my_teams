/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

namespace my_teams {
namespace server {
ClientSession::ClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket): _socket{socket}
{
}

void ClientSession::start()
{
    handleRead();
}

void ClientSession::handleRead()
{
    _buffer.resize(1024);

    _socket->asyncReadSome(network::buffer(_buffer, _buffer.size()),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cout << err.message() << std::endl;
                handleRead();
            } else {
                _buffer.resize(bytes);
                std::cout << "Received from client:" << std::endl;
                std::cout << _buffer << std::endl;
                handleWrite();
            }
        });
}

void ClientSession::handleWrite()
{
    _socket->asyncWrite(network::buffer("Wellcome!!!"),
        [this](const std::error_code &err, const std::size_t &) {
            if (err) {
                std::cout << err.message() << std::endl;
                handleWrite();
            } else {
                std::cout << "Message sent successfuly" << std::endl;
                handleRead();
            }
        });
}
} // server
} // my_teams
