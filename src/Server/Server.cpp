/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

namespace my_teams {
namespace server {
Server::Server(const int &port): _router{port}, _db{"db"}
{}

void Server::run()
{
    _router.get("/home", {clientHelp(_db)});

    _router.run();
}

Server::Handler Server::clientHelp(liteORM::Database &)
{
    return [](network::Router<UserState>::Context *ctx) {
        nlohmann::json body;
        body["message"] = "Help message";
        ctx->jsonp(network::StatusCode::STATUS_OK, body);
    };
}
} // server
} // my_teams
