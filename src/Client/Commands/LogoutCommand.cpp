/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "logging_client.h"
#include "Commands/LogoutCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool LogoutCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    req["method"] = network::Method::POST;
    req["path"] = "/logout";
    req["body"] = {};
    client.send(req.dump(), [](auto, auto){});

    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    User user = response.body;

    client_event_logged_out(user.uuid.c_str(), user.name.c_str());
    return true;
}

bool LogoutCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> LogoutCommand::create()
{
    return std::unique_ptr<IShellCommand>(new LogoutCommand());
}

}
