/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_CREATE_HPP
#define MYTEAMS_CREATE_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class CreateCommand : public IShellCommand {
public:

    CreateCommand() = default;
    ~CreateCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> arg) override;
    bool execute(Shell &shell, std::vector<std::string> arg) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
