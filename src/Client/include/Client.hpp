/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#ifndef MY_TEAMS_CLIENT_HPP
#define MY_TEAMS_CLIENT_HPP

#include <cstdint>
#include <map>
#include "IoContext.hpp"

constexpr int EXIT_EPITECH = 84;

constexpr size_t MAX_USE_ARGS = 4;

namespace my_teams::client {

enum CommandContextType : uint8_t {
        TEAM = 0,
        CHANNEL,
        THREAD,
        UNDEFINED,
        USER,
};

class Client {
public:
    explicit Client(const int &port, const std::string &ipAddress);

    void send(const std::string &,
        const network::ConnectedSocket::Callback &handler) const;

    std::string receive();

    const CommandContextType &getContext() const noexcept;
    void setContext(CommandContextType newContext) noexcept;

    const std::string &getUserId() const noexcept;
    void setUserId(std::string &uuid) noexcept;

    const std::string &getTeamId() const noexcept;
    void setTeamId(std::string &uuid) noexcept;

    const std::string &getChannelId() const noexcept;
    void setChannelId(std::string &uuid) noexcept;

    const std::string &getThreadId() const noexcept;
    void setThreadId(std::string &uuid) noexcept;

    void resetContext() noexcept;

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
