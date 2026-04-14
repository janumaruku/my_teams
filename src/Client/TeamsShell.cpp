/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "TeamsShell.hpp"
#include "Commands/HelpCommand.hpp"
#include "Shell.hpp"

namespace my_teams::client {

TeamsShell::TeamsShell(Client &client, std::string name,
    std::string prompt):
    Shell::Shell(std::move(name), std::move(prompt)),
    _client(client)
{
    registerCommands();
}

void TeamsShell::registerCommands()
{
    _shellCommandFactory.registerCreator<shell::HelpCommand>("/help");
}

void TeamsShell::run()
{
    Shell::run();
}

Client &TeamsShell::getClient() const noexcept
{
    return _client;
}
}
