/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#ifndef MY_TEAMS_SERVER_HPP
#define MY_TEAMS_SERVER_HPP

#include "Database.hpp"
#include "Router.hpp"

namespace my_teams {
namespace server {

class Server {
    struct UserState {
        User user;
        bool isLoggedIn;
    };

public:
    explicit Server(const int &port);

    void run();

private:
    network::Router<UserState> _router;
    liteORM::Database _db;

    using Handler = std::function<void(network::Router<UserState>::Context *)>;

    static Handler clientHelp(liteORM::Database &database);
};

} // server
} // my_teams

#endif //MY_TEAMS_SERVER_HPP
