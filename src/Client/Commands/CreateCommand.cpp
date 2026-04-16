/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
**
*/

#include "Commands/CreateCommand.hpp"

#include <algorithm>

#include "Client.hpp"
#include "jsonParser.hpp"
#include "LoggingClient.hpp"
#include "Router.hpp"
#include "Serializer.hpp"
#include "TeamsShell.hpp"
#include "../../Network/include/Serializer.hpp"

namespace my_teams::client::shell {

bool CreateCommand::operator()(Shell &shell, std::vector<std::string> args)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    req["method"] = network::Method::POST;
    std::string path;

    auto context = client.getContext();

    switch (context) {
    case USER:
        createTeam(req, client, args);
        break;
    case TEAM:
        createChannel(req, client, args);
        break;
    case CHANNEL:
        createThread(req, client, args);
        break;
    case THREAD:
        createComment(req, client, args);
        break;
    default:
        break;
    }

    client.send(req.dump());

    const std::string jsonString = client.receive();
    const Response response      = nlohmann::json::parse(jsonString);

    createLog(context, response);
    return true;
}

bool CreateCommand::execute(Shell &shell, const std::vector<std::string> cmd)
{
    return operator()(shell, cmd);
}

std::unique_ptr<IShellCommand> CreateCommand::create()
{
    return std::unique_ptr<IShellCommand>(new CreateCommand());
}

void CreateCommand::createTeam(nlohmann::json &req, const Client &client,
    const std::vector<std::string> &args)
{
    req["path"]                = "/home/users/" + client.getUserId() + "/team";
    req["body"]["team_name"]   = args[0];
    req["body"]["description"] = args[1];
}

void CreateCommand::createChannel(nlohmann::json &req,
    const Client &client, const std::vector<std::string> &args)
{
    req["path"] = "/home/users/" + client.getUserId() + "/channel";
    req["body"]["team_id"] = client.getTeamId();
    req["body"]["channel_name"] = args[0];
    req["body"]["description"] = args[1];
}

void CreateCommand::createThread(nlohmann::json &req, const Client &client,
    const std::vector<std::string> &args)
{
    req["path"] = "/home/users/" + client.getTeamId() + "/thread";
    req["body"]["team_id"] = client.getTeamId();
    req["body"]["channel_id"] = client.getChannelId();
    req["body"]["thread_title"] = args[0];
    req["body"]["thread_message"] = args[1];
}

void CreateCommand::createComment(nlohmann::json &req, const Client &client,
    const std::vector<std::string> &args)
{
    req["path"] = "/home/users/" + client.getTeamId() + "/comment";
    req["body"]["team_id"] = client.getTeamId();
    req["body"]["channel_id"] = client.getChannelId();
    req["body"]["thread_id"] = client.getChannelId();
    req["body"]["comment_body"] = args[0];
}

void CreateCommand::createLog(const CommandContextType &context,
    const Response &response)
{
    switch (context) {
    case USER: {
        const Team team = response.body;
        client_event_team_created(team.uuid.c_str(), team.name.c_str(),
            team.description.c_str());
        break;
    }
    case TEAM: {
        const Channel channel = response.body;
        client_event_channel_created(channel.uuid.c_str(), channel.name.c_str(),
            channel.description.c_str());
        break;
    }
    case CHANNEL: {
        const Thread thread = response.body;
        client_event_thread_created(thread.uuid.c_str(), thread.userId.c_str(),
            std::chrono::system_clock::to_time_t(thread.createdAt),
            thread.title.c_str(), thread.body.c_str());
        break;
    }
    default:
        break;
    }
}

} // namespace my_teams::client::shell
