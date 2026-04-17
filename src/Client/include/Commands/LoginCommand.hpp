/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_LOGIN_HPP
#define MYTEAMS_LOGIN_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class LoginCommand : public IShellCommand {
public:

    LoginCommand() = default;
    ~LoginCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> args) override;
    bool execute(Shell &shell, std::vector<std::string> args) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
