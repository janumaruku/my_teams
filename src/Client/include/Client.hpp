/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#ifndef MY_TEAMS_CLIENT_HPP
#define MY_TEAMS_CLIENT_HPP

#include "IoContext.hpp"
#include "stdint.h"

constexpr int EXIT_EPITECH = 84;

namespace my_teams::client {

class Client {
public:
    explicit Client(const int &port, const std::string &ipAddress);

    void send(const std::string &,
        const network::ConnectedSocket::Callback &handler) const;

    std::string receive();

    enum CommandContextType : uint8_t {
        USER = 0,
        TEAM,
        CHANNEL,
        THREAD
    };

private:
    network::IOContext _ioContext;
    network::ConnectedSocket _socket;
    std::string _buffer;
    std::string _transmission;

    void handleWrite();

    void handleRead();
    CommandContextType _context;

    std::string _userId;
    std::string _teamId;
    std::string _channelId;
    std::string _threadId;
};

}

#endif //MY_TEAMS_CLIENT_HPP
