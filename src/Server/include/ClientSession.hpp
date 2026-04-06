/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** ClientSession
*/

#ifndef MY_TEAMS_CLIENTSESSION_HPP
#define MY_TEAMS_CLIENTSESSION_HPP

#include <memory>

#include "ConnectedSocket.hpp"

namespace my_teams {
namespace server {

class ClientSession {
public:
    explicit ClientSession(
        const std::shared_ptr<network::ConnectedSocket> &socket);

    void start();

private:
    std::shared_ptr<network::ConnectedSocket> _socket;
    std::string _buffer;

    void handleRead();

    void handleWrite();
};

} // server
} // my_teams

#endif //MY_TEAMS_CLIENTSESSION_HPP
