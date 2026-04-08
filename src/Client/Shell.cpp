/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <string>
#include <memory>
#include "Shell.hpp"
#include "ShellExit.hpp"
#include "Client.hpp"

namespace my_teams::client {

Shell::Shell() :
    _name(BASE_NAME),
    _prompt(BASE_PROMPT),
    _client(nullptr)
{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
}

Shell::Shell(const Client &client, std::string name, std::string prompt) : 
    _name(std::move(name)),
    _prompt(std::move(prompt)),
    _client(std::make_unique<Client>(client))
{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
}
    
}
