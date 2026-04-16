/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "LoggingClient.hpp"
#include "Commands/CreateCommand.hpp"
#include <algorithm>
#include "Router.hpp"
#include "Serializer.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool CreateCommand::operator()(Shell &shell,
    std::vector<std::string> args)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    req["method"] = network::Method::POST;
    std::string path;
    
    auto context = client.getContext();
    
    if (context == USER) {
        path = "/home/users/" + client.getUserId() + "/team";
    }
    if (context == TEAM) {
        path = "/home/users/" + client.getUserId() + "/channel";
    }
    if (context == CHANNEL) {
        path = "/home/users/" + client.getUserId() + "/thread";
    }
    if (context == THREAD) {
        path = "/home/users/" + client.getUserId() + "/comment";
    }

    req["path"] = "/home" + path;
    if (context == THREAD) {
        req["body"] = args.at(0);
    } else {
        req["body"] = {args.at(0), args.at(1)};
    }

    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString); 
    return true;
}

bool CreateCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> CreateCommand::create()
{
    return std::unique_ptr<IShellCommand>(new CreateCommand());
}

}
