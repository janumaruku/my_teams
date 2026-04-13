/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Commands/LoginCommand.hpp"
#include "Router.hpp"
#include "jsonParser.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool LoginCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    const auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    req["method"] = network::Method::POST;
    req["path"] = "/login";
    req["header"] = {}
    req["body"] = {
			{"username", "Jean"},
			{"password", ""}
	};
    client->send(req.dump());
    return true;
}

bool LoginCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> LoginCommand::create()
{
    return std::unique_ptr<IShellCommand>(new LoginCommand());
}

}
