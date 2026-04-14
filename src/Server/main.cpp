/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include <string>
#include "Acceptor.hpp"
#include "Client.hpp"
#include "IoContext.hpp"
#include "Router.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        return EXIT_EPITECH;
    int port = std::stoi(av[1]);
    network::Router<bool> router{port};

    router.get("/home", {[](network::Router<bool>::Context *ctx) {
        ctx->abortWithStatus(network::StatusCode::STATUS_OK);
    }});

    router.run();
    return 0;
}
