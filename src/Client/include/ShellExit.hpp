/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** ShellExit
*/

#ifndef MYTEAMS_SHELLEXIT_HPP
#define MYTEAMS_SHELLEXIT_HPP

#include <memory>
#include "IShellCommand.hpp"
#include "Shell.hpp"

namespace my_teams::client::shell {

class ShellExit: public IShellCommand {
public:
    ShellExit() = default;

    ~ShellExit() override = default;

    bool operator()(Shell &shell,
        std::vector<std::string> cmd) override;

    bool execute(Shell &shell,
        std::vector<std::string> cmd) override;

    static std::unique_ptr<IShellCommand> create();
};
}

// #include "../src/ShellExit.tpp"

#endif //MYTEAMS_SHELLEXIT_HPP
