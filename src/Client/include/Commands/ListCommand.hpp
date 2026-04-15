/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_LIST_HPP
#define MYTEAMS_LIST_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class ListCommand : public IShellCommand {
public:

    ListCommand() = default;
    ~ListCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> cmd) override;
    bool execute(Shell &shell, std::vector<std::string> cmd) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
