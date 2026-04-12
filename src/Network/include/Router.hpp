/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router
*/

#ifndef MY_TEAMS_ROUTER_HPP
#define MY_TEAMS_ROUTER_HPP

#include "Acceptor.hpp"
#include "IoContext.hpp"

namespace network {
template <typename TClientState> class Router {
private:
    IOContext _ioContext;
    Acceptor _acceptor;
    std::unordered_map<std::shared_ptr<ConnectedSocket>, TClientState> _clients;
};

} // namespace network

#endif // MY_TEAMS_ROUTER_HPP
