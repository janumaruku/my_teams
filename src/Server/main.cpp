/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Acceptor.hpp"
#include "IoContext.hpp"
#include "Router.hpp"
#include "Server.hpp"

int main()
{
    network::Router<bool> router{10000};

    router.get("/home", {[](network::Router<bool>::Context *ctx) {
        ctx->abortWithStatus(network::StatusCode::STATUS_OK);
    }});

    router.run();
    return 0;
}
