/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <cstdint>
#include <iostream>
#include "Commands/UseCommand.hpp"
#include "Client.hpp"
#include "Router.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool UseCommand::operator()(Shell &shell,
    std::vector<std::string> args)
{
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    
    if (args.empty()) {
        client.setContext(my_teams::client::CommandContextType::UNDEFINED);
        return true;
    }

    uint8_t contextIdx = 0;
    std::cout << "Args size:" << args.size() << std::endl;

    for (size_t idx = 0; idx < args.size(); ++idx) {
        switch (idx) {
            case TEAM:
                std::cout << "TEAM" << std::endl;
                client.setTeamId(args.at(idx));
                break;
            case CHANNEL:
                std::cout << "CHANNEL" << std::endl;
                client.setChannelId(args.at(idx));
                break;
            case THREAD:
                std::cout << "THREAD" << std::endl;
                client.setThreadId(args.at(idx));
                break;
            default:
                std::cout << "NOPE" << std::endl;
                break;
        }
        contextIdx++;
    }
    client.setContext(static_cast<CommandContextType>(contextIdx));
    return true;
}

bool UseCommand::execute(Shell &shell,
    const std::vector<std::string> args)
{
    return operator ()(shell, args);
}

std::unique_ptr<IShellCommand> UseCommand::create()
{
    return std::unique_ptr<IShellCommand>(new UseCommand());
}

}
