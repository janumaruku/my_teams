/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <algorithm>
#include <string>
#include "Commands/SubscribedCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"

#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "logging_client.h"

namespace my_teams::client::shell {

bool SubscribedCommand::operator()(Shell &shell,
    std::vector<std::string> arg)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    std::string path = arg.empty() ? "/home/users/" + arg.at(1) + "/teams" : "/home/teams/" + arg.at(1) + "/users";
    req["path"] = path;
    req["method"] = network::Method::GET;
    req["body"] = {};

    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    if (response.statusCode != network::StatusCode::STATUS_OK) {
        std::cout << response.body.at("error_message") << std::endl;
        return false;
    }

    Team team = response.body;
    client_print_subscribed(client.getUserId().c_str(), team.uuid.c_str());
    return true;
}

bool SubscribedCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> SubscribedCommand::create()
{
    return std::unique_ptr<IShellCommand>(new SubscribedCommand());
}

}
