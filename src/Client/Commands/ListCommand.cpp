/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Commands/ListCommand.hpp"
#include <chrono>
#include <map>
#include <stdexcept>
#include "Router.hpp"
#include "Serializer.hpp"
#include "Types.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "LoggingClient.hpp"

namespace my_teams::client::shell {

bool ListCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    
    req["method"] = network::Method::GET;
    std::string path;
    
    auto context = client.getContext();

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

    req["path"] = "/home" + path;
    req["body"] = {};

    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);
   

    switch (context) {
        case TEAM: {
            std::vector<Team> teams = response.body;
            for (const auto &team : teams) {
                client_print_teams(team.uuid.c_str(), team.name.c_str(), team.description.c_str());
            }
            break;
        }
        case CHANNEL: {
            std::vector<Channel> channels = response.body;
            for (const auto &channel : channels) {
                client_team_print_channels(channel.uuid.c_str(), channel.name.c_str(), channel.description.c_str());
            }
            break;
        }
        case THREAD: {
            std::vector<Thread> threads = response.body;
            for (const auto &thread : threads) {
                client_channel_print_threads(thread.uuid.c_str(), thread.userId.c_str(),
                                            std::chrono::system_clock::to_time_t(thread.createdAt),
                                            thread.title.c_str(),
                                            thread.body.c_str());
            }
            break;
        }
        default:
            break;
    }
    return true;
}

bool ListCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> ListCommand::create()
{
    return std::unique_ptr<IShellCommand>(new ListCommand());
}

}
