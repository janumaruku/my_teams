/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_HELP_HPP
#define MYTEAMS_HELP_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class HelpCommand : public IShellCommand {
public:

    HelpCommand() = default;
    ~HelpCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> cmd) override;
    bool execute(Shell &shell, std::vector<std::string> cmd) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
