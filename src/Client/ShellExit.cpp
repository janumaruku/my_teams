/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Commands/ShellExit.hpp"
#include "Commands/ShellExitException.hpp"
#include "Shell.hpp"

namespace my_teams::client::shell {
bool ShellExit::operator()(Shell &,
    std::vector<std::string>)
{
    throw ShellExitException();
}

bool ShellExit::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator()(shell, cmd);
}

std::unique_ptr<IShellCommand> ShellExit::create()
{
    return std::unique_ptr<IShellCommand>(new ShellExit());
}

}
