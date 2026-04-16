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
#include "Commands/ListCommand.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "LoggingClient.hpp"
#include "logging_client.h"

namespace my_teams::client::shell {

bool SubscribedCommand::operator()(Shell &shell,
    std::vector<std::string> arg)
{
    bool list_teams = false;
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    std::string path; 
    if (arg.empty()) {
        path = "/home/users/" + arg.at(0) + "/teams";
        list_teams = true;
    } else {
        path = "/home/teams/" + arg.at(0) + "/users";
    }
    req["path"] = path;
    req["method"] = network::Method::GET;
    req["body"] = {};

    client.send(req.dump());
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    if (response.statusCode != network::StatusCode::STATUS_OK) {
        std::cout << response.body.at("error_message") << std::endl;
        return false;
    }

    if (list_teams) {
        std::vector<Team> teams = response.body;
        ListCommand::listTeams(teams);
        return true;
    }
    std::vector<User> users = response.body;
    for (const auto &user : users)
        client_print_users(user.uuid.c_str(),
                        user.name.c_str(),
                        static_cast<int>
                        (response.statusCode != network::StatusCode::UNAUTHORIZED));
    return true;
}

bool SubscribedCommand::execute(Shell &shell,
    const std::vector<std::string> args)
{
    return operator ()(shell, args);
}

std::unique_ptr<IShellCommand> SubscribedCommand::create()
{
    return std::unique_ptr<IShellCommand>(new SubscribedCommand());
}

}
