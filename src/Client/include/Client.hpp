/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#ifndef MY_TEAMS_CLIENT_HPP
#define MY_TEAMS_CLIENT_HPP

#include "IoContext.hpp"

namespace my_teams {
namespace client {

class Client {
public:
    explicit Client(const int &port, const std::string &ipAddress);

    void start();

private:
    network::IOContext _ioContext;
    network::ConnectedSocket _socket;
    std::string _buffer;

    void handleWrite();

    void handleRead();
};

} // client
} // my_teams

#endif //MY_TEAMS_CLIENT_HPP
