/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

namespace my_teams {
namespace server {
Server::Server(const int &port, const std::string &ipAddress): _acceptor(
    _ioContext, network::Endpoint{port, ipAddress})
{
}

void Server::run()
{
    startAccept();

    _ioContext.run();
}

void Server::startAccept()
{
    _acceptor.asyncAccept([this](const std::error_code &err,
        const std::shared_ptr<network::ConnectedSocket> &sock) {
            if (err) {
                std::cerr << err.message() << std::endl;
            } else {
                std::cout << "Connection received from " << sock->
                    remoteEndpoint().getHostname() << ":" << sock->
                    remoteEndpoint().getPort() << std::endl;
                _clientSockets.push_back(sock);
            }
            startAccept();
        });
}
} // server
} // my_teams
