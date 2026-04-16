/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_MESSAGES_HPP
#define MYTEAMS_MESSAGES_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class MessagesCommand : public IShellCommand {
public:

    MessagesCommand() = default;
    ~MessagesCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> args) override;
    bool execute(Shell &shell, std::vector<std::string> args) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
