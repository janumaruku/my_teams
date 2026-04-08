/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef ISHELL_COMMAND_HPP
#define ISHELL_COMMAND_HPP

#include <vector>
#include <string>

namespace my_teams::client {

class Shell;

namespace shell {

class IShellCommand {
public:
    IShellCommand() = default;

    virtual ~IShellCommand() = default;

    virtual bool operator()(
        Shell &shell,
        std::vector<std::string> cmd) = 0;

    virtual bool execute(Shell &shell,
        std::vector<std::string> cmd) = 0;
};

}
}
#endif // !ISHELL_COMMAND_HPP
