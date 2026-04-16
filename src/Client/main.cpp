/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** main
*/

#include <cstdlib>
#include <exception>
#include <iostream>
#include "Client.hpp"
#include "Shell.hpp"
#include "TeamsShell.hpp"

int main(int ac, char **av)
{
    if (ac < 2 || ac > 3)
        return EXIT_EPITECH;

    if (ac == 2 && std::string{av[1]} == "--help") {
        my_teams::client::Client::help();
        return 0;
    }

    try {
        const int port = std::stoi(av[2]);

        my_teams::client::Client client{port, av[1]};
        my_teams::client::TeamsShell
            shell(client, "my_teams_cli_shell", my_teams::client::BASE_PROMPT);

        shell.run();
    } catch (const std::exception e) {
        std::cout << e.what() << std::endl;
        return EXIT_EPITECH;
    }
    return EXIT_SUCCESS;
}
