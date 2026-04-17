/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <functional>
#include "Commands/InfoCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "LoggingClient.hpp"

namespace my_teams::client::shell {

bool InfoCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient(); 
    
    std::string path;
    
    auto context = client.getContext();
    if (context == USER) {
        path += "/users/" + client.getUserId();
        goto json;
    }
    if (context >= TEAM) {
        path += "/";
        path += client.getTeamId();
    } else {
        return false;
    }
    if (context >= CHANNEL) {
        path += client.getChannelId();
        path += "/";
    }
    if (context == THREAD) {
        path += client.getThreadId();
    }
    
json:
    req["method"] = network::Method::GET;
    req["path"] = "/home" + path;
    req["body"] = {};


    client.send(req.dump());
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);
    if (context == USER) {
        User user = response.body;
        client_print_user(user.uuid.c_str(), user.name.c_str(),
        static_cast<int>(response.statusCode == network::StatusCode::STATUS_OK));
    }

    switch (context) {
        case TEAM: {
            Team team = response.body;
            client_print_team(team.uuid.c_str(), team.name.c_str(), team.description.c_str());
            break;
        }
        case CHANNEL: {
            Channel channel = response.body;
            client_print_channel(channel.uuid.c_str(), channel.name.c_str(), channel.description.c_str());
            break;
        }
        case THREAD: {
            Thread thread = response.body;
            client_print_thread(thread.uuid.c_str(), thread.userId.c_str(),
                                std::chrono::system_clock::to_time_t(thread.createdAt),
                                thread.title.c_str(),
                                thread.body.c_str());
            }
            break;
        default:
            break;
        }
    return true;
}

bool InfoCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> InfoCommand::create()
{
    return std::unique_ptr<IShellCommand>(new InfoCommand());
}

}
