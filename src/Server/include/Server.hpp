/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#ifndef MY_TEAMS_SERVER_HPP
#define MY_TEAMS_SERVER_HPP

#include "Acceptor.hpp"
#include "ClientSession.hpp"
#include "IoContext.hpp"

namespace my_teams {
namespace server {

class Server {
public:
    explicit Server(const int &port, const std::string &ipAddress = "");

    void run();

private:
    network::IOContext _ioContext;
    network::Acceptor _acceptor;
    std::vector<std::shared_ptr<ClientSession>> _clientSessions;

    void startAccept();
};

} // server
} // my_teams

#endif //MY_TEAMS_SERVER_HPP
