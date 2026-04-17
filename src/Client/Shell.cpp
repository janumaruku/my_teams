/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/


#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include "Shell.hpp"
#include "StringUtils.hpp"
#include "TeamsShell.hpp"
#include "Commands/ShellExit.hpp"
#include "Commands/ShellExitException.hpp"
#include "Commands/ShellCommandException.hpp"

namespace my_teams::client {

// using base parameters would be better to avoid duplication but the compiler refuses to move constexpr, which is normal

Shell::Shell() : _name(BASE_NAME), _prompt(BASE_PROMPT)
{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
}

Shell::Shell(std::string name, std::string prompt) :
     _name(std::move(name)),
    _prompt(std::move(prompt))

{
    _shellCommandFactory.registerCreator<shell::ShellExit>(EXIT_PROMPT);
}

bool Shell::executeCommand(const std::vector<std::string> &cmd)
{

    try {
        std::vector<std::string> args(cmd.begin() + 1, cmd.end());
        const auto command = _shellCommandFactory.create(cmd.at(0));
        return command->execute(*this, args);
    } catch (const std::exception &e) {
        throw;
    }
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
        try {
            std::vector<std::string> cmd;
            auto quotesCount = std::ranges::count(line, '"');
            if (quotesCount == 0 || quotesCount % 2 != 0)
                cmd = utils::StringUtils::splitQuoted(line);
            else
                throw std::invalid_argument("");
            executeCommand(cmd);
        } catch (const shell::ShellExitException) {
            return;
        } catch (const shell::ShellCommandException) {
            throw;
        } catch (const std::invalid_argument &e) {
            continue;
        } catch (const std::runtime_error) {
            continue;
        }
    }
}
}
