/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Commands/HelpCommand.hpp"
#include "Router.hpp"
#include "jsonParser.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool HelpCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    req["method"] = network::Method::GET;
    req["path"] = "/help";
    req["body"] = {};
    const auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
       
    
    return true;
}

bool HelpCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> HelpCommand::create()
{
    return std::unique_ptr<IShellCommand>(new HelpCommand());
}

}
