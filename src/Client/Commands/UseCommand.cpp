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
    
    //
    for (const auto &word : args) {
        std::cout << "Word: \"" << word << "\"" << std::endl;
    }
    //

    for (size_t idx = 0; idx < MAX_USE_ARGS; ++idx) {
        if (idx >= args.size() || args.at(idx).empty()) {
            if (idx == 0)
                client.setContext(CommandContextType::UNDEFINED);
            return true;
        }
        switch (idx) {
            case USER:
                client.setUserId(args.at(idx));
                client.setContext(CommandContextType::USER);
                break;

            case TEAM:
                client.setTeamId(args.at(idx));
                client.setContext(CommandContextType::TEAM);
                break;

            case CHANNEL:
                client.setChannelId(args.at(idx));
                client.setContext(CommandContextType::CHANNEL);
                break;

            case THREAD:
                client.setThreadId(args.at(idx));
                client.setContext(CommandContextType::THREAD);
                break;
            default:
                break;
        }
    }
    std::cout << "Context =" << client.getContext() << std::endl;
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
