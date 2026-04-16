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
    _router.use([](network::Router<bool>::Context *ctx) {
        std::cout << "ARMAGEDDON 1" << std::endl;
        ctx->next();
    });



    _router.get("/home", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});
    _router.post("/tebe/true", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});
    _router.post("/tebe/false", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});



    auto group = _router.group("/home");
    group.use([](network::Router<bool>::Context *ctx) {
        std::cout << "ARMAGEDDON 4" << std::endl;
        ctx->next();
    });
    group.get("/batard/:id", {[](network::Router<bool>::Context *ctx) {
            ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});



    _router.run();
}
} // server
} // my_teams
