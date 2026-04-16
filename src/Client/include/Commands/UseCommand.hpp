/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_USE_HPP
#define MYTEAMS_USE_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class UseCommand : public IShellCommand {
public:

    UseCommand() = default;
    ~UseCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> args) override;
    bool execute(Shell &shell, std::vector<std::string> args) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
