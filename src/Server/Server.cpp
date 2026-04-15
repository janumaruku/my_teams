/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

namespace my_teams {
namespace server {
Server::Server(const int &port): _router{port}
{}

void Server::run()
{
    _router.get("/help", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});

    _router.run();
}
} // server
} // my_teams
