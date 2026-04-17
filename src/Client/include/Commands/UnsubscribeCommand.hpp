/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_UNSUBSCRIBE_HPP
#define MYTEAMS_UNSUBSCRIBE_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class UnsubscribeCommand : public IShellCommand {
public:

    UnsubscribeCommand() = default;
    ~UnsubscribeCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> arg) override;
    bool execute(Shell &shell, std::vector<std::string> arg) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
