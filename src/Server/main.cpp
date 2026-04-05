/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Acceptor.hpp"
#include "IoContext.hpp"
#include "Server.hpp"

int main()
{
    my_teams::server::Server server{10000};

    server.run();
}
