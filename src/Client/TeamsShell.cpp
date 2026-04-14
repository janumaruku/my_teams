/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "TeamsShell.hpp"
#include "Shell.hpp"

namespace my_teams::client {

TeamsShell::TeamsShell():
    Shell::Shell(BASE_NAME, BASE_PROMPT),
    _client(nullptr)
{
    registerCommands();
}

TeamsShell::TeamsShell(std::string name, std::string prompt):
    Shell::Shell(std::move(name), std::move(prompt)),
    _client(nullptr)

{
    registerCommands();
}

TeamsShell::TeamsShell(const Client &client, std::string name,
    std::string prompt):
    Shell::Shell(std::move(name), std::move(prompt)),
    _client(std::make_unique<Client>(client))
{
    registerCommands();
}

void TeamsShell::registerCommands()
{
    // _shellCommandFactory.registerCreator<shell::HelpCommand>(EXIT_PROMPT);
}

void TeamsShell::run()
{
    Shell::run();
}

Client *TeamsShell::getClient() const noexcept
{
    return _client.get();
}
}
