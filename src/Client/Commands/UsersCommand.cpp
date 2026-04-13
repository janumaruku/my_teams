/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Commands/UsersCommand.hpp"
#include "Router.hpp"
#include "jsonParser.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool UsersCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    req["method"] = network::Method::GET;
    req["path"] = "/users";
    req["body"] = {};
    const auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
       
    return true;
}

bool UsersCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> UsersCommand::create()
{
    return std::unique_ptr<IShellCommand>(new UsersCommand());
}

}
