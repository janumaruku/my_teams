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
    network::Router<int> router{10000};

    router.run();

    return 0;
}
