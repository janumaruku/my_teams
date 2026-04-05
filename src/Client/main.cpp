/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** main
*/

#include "Client.hpp"
#include "ConnectedSocket.hpp"
#include "IoContext.hpp"

int main()
{
    my_teams::client::Client client{10000, "127.0.0.1"};

    client.start();

    return 0;
}
