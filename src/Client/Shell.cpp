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
#include "ShellExitException.hpp"
#include "ShellCommandException.hpp"
#include "Client.hpp"

namespace my_teams::client {

// using base parameters would be better to avoid duplication but the compiler refuses to move constexpr, which is normal

Shell::Shell() :
    _name(BASE_NAME),
    _prompt(BASE_PROMPT),
    _client(nullptr)
{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
}

Shell::Shell(std::string name, std::string prompt) :
     _name(std::move(name)),
    _prompt(std::move(prompt)),
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
    
void Shell::run()
{
    std::string line;

    while (true) {
        std::cout << _prompt;
        if (!std::getline(std::cin, line)) {
            std::cout.flush();
            return;
        }
        if (ShellUtils::isEmptyLine(line))
            continue;
        std::vector<std::string> cmd = ShellUtils::split(line, ' ');
        try {
            executeCommand(cmd);
        } catch (const shell::ShellExitException) {
            return;
        } catch (const shell::ShellCommandException) {
            throw;
        }
    }
}
}
