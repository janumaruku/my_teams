/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#ifndef MY_TEAMS_CLIENT_HPP
#define MY_TEAMS_CLIENT_HPP

#include "IoContext.hpp"

constexpr int EXIT_EPITECH = 84;

namespace my_teams::client {

class Client {
public:
    explicit Client(const int &port, const std::string &ipAddress);

    void send(const std::string &,
        const network::ConnectedSocket::Callback &handler) const;

    std::string receive();

    // void start();

private:
    network::IOContext _ioContext;
    network::ConnectedSocket _socket;
    std::string _buffer;
    std::string _transmission;

    void handleWrite();

    void handleRead();
};

}

#endif //MY_TEAMS_CLIENT_HPP
