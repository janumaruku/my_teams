/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <functional>
#include "Commands/UnsubscribeCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"

#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "LoggingClient.hpp"

namespace my_teams::client::shell {

bool UnsubscribeCommand::operator()(Shell &shell,
    std::vector<std::string> arg)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    req["method"] = network::Method::DELETE;
    req["path"] = "/home/users/" + client.getUserId() + "unsubscribe";
    req["body"] = {{"team_id", arg.at(0)}};

    client.send(req.dump(), [](auto, auto){});

    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);  
    client_print_unsubscribed(client.getUserId().c_str(), arg.at(0).c_str());
    return true;
}

bool UnsubscribeCommand::execute(Shell &shell,
    const std::vector<std::string> arg)
{
    return operator ()(shell, arg);
}

std::unique_ptr<IShellCommand> UnsubscribeCommand::create()
{
    return std::unique_ptr<IShellCommand>(new UnsubscribeCommand());
}

}
