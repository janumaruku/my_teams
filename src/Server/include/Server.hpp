/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#ifndef MY_TEAMS_SERVER_HPP
#define MY_TEAMS_SERVER_HPP

#include "Router.hpp"

namespace my_teams {
namespace server {

class Server {
public:
    explicit Server(const int &port);

    void run();

private:
    network::Router<bool> _router;
};

} // server
} // my_teams

#endif //MY_TEAMS_SERVER_HPP
