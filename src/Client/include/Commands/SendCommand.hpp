/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_SEND_HPP
#define MYTEAMS_SEND_HPP

#include <memory>
#include "IShellCommand.hpp"

namespace my_teams::client::shell {

class SendCommand : public IShellCommand {
public:

    SendCommand() = default;
    ~SendCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> cmd) override;
    bool execute(Shell &shell, std::vector<std::string> cmd) override;

    static std::unique_ptr<IShellCommand> create();
};


}
#endif
