/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include "Shell.hpp"
#include "ShellExit.hpp"
#include "ShellExitException.hpp"
#include "ShellCommandException.hpp"
#include "Client.hpp"

namespace my_teams::client {

// using base parameters would be better to avoid duplication but the compiler refuses to move constexpr, which is normal

Shell::Shell() noexcept :
    _name(BASE_NAME),
    _prompt(BASE_PROMPT),
    _client(nullptr)
{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
    registerCommands();
}

Shell::Shell(std::string name, std::string prompt) noexcept :
     _name(std::move(name)),
    _prompt(std::move(prompt)),
    _client(nullptr)

{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
    registerCommands();
}

Shell::Shell(const Client &client, std::string name, std::string prompt) noexcept : 
    _name(std::move(name)),
    _prompt(std::move(prompt)),
    _client(std::make_unique<Client>(client))
{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
    registerCommands();
}

bool Shell::executeCommand(const std::vector<std::string> &cmd)
{
    try {
        const auto command = _shellCommandFactory.create(cmd[0]);
        return command->execute(*this, cmd);
    } catch (const std::exception &e) {
        throw;
    }
}

void Shell::registerCommands()
{
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
        } catch (const std::runtime_error) {
            continue;
        }
    }
}
}
