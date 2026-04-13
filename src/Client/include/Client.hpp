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

    void send(const std::string &);
    void start();

private:
    network::IOContext _ioContext;
    network::ConnectedSocket _socket;
    std::string _buffer;

    void handleWrite();

    void handleRead();
};

}

#endif //MY_TEAMS_CLIENT_HPP
