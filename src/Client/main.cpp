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
#include "Commands/ShellCommandException.hpp"
#include "ConnectedSocket.hpp"
#include "IoContext.hpp"

int main()
{
    my_teams::client::Client client{10000, "127.0.0.1"};
    my_teams::client::TeamsShell
    shell(client, "my_teams_cli_shell", my_teams::client::BASE_PROMPT);
    
    try {
        shell.run();
    } catch (const my_teams::client::shell::ShellCommandException e) {
        std::cout << e.what() << std::endl;
        return EXIT_EPITECH;
    }
    return EXIT_SUCCESS;
}
