/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_USER_HPP
#define MYTEAMS_USER_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class UserCommand : public IShellCommand {
public:

    UserCommand() = default;
    ~UserCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> cmd) override;
    bool execute(Shell &shell, std::vector<std::string> cmd) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
