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
        std::cout << "ARMAGGEDON 1" << std::endl;
        ctx->next();
    });
    _router.use([](network::Router<bool>::Context *ctx) {
        std::cout << "ARMAGGEDON 2" << std::endl;
        ctx->next();
    });
    _router.use([](network::Router<bool>::Context *ctx) {
        std::cout << "ARMAGGEDON 3" << std::endl;
        ctx->next();
    });

    _router.get("/help", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});
    _router.post("/home/:id", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});
    _router.post("/home/:id", {[](network::Router<bool>::Context *ctx) {
        ctx->jsonp(network::StatusCode::STATUS_OK,
            {{"help_message", "Help message"}});
    }});

    _router.run();
}
} // server
} // my_teams
