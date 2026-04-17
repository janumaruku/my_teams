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

    client.send(req.dump());
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString); 

    switch (context) {
        case TEAM:
            listTeams(response.body);
            break;
        case CHANNEL:
            listChannels(response.body);
            break;
        case THREAD:
            listThreads(response.body);
            break;
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

void ListCommand::logTeam(const Team &team)
{
     client_print_teams(team.uuid.c_str(), team.name.c_str(), team.description.c_str());

}

void ListCommand::listTeams(const std::vector<Team> &teams)
{
    for (const auto &team : teams)
        logTeam(team);
}

void ListCommand::logChannel(const Channel &channel)
{
    client_team_print_channels(channel.uuid.c_str(), channel.name.c_str(), channel.description.c_str());
}

void ListCommand::listChannels(const std::vector<Channel> &channel)
{
    for (const auto &channel : channel)
        logChannel(channel);

}

void ListCommand::logThread(const Thread &thread)
{
client_channel_print_threads(
    thread.uuid.c_str(), thread.userId.c_str(),
    std::chrono::system_clock::to_time_t(thread.createdAt),
    thread.title.c_str(),
    thread.body.c_str());

}

void ListCommand::listThreads(const std::vector<Thread> &threads)
{
    for (const auto &thread : threads)
        logThread(thread);

}

}
