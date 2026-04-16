/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Commands/SubscribeCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"

#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "LoggingClient.hpp"

namespace my_teams::client::shell {

bool SubscribeCommand::operator()(Shell &shell,
    std::vector<std::string> arg)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    req["method"] = network::Method::POST;
    req["path"] = "/home/users/" + client.getUserId() + "/subscribe";
    req["body"] = {{"team_id", arg.at(0)}};

    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    if (response.statusCode != network::StatusCode::STATUS_OK) {
        std::cout << response.body.at("error_message") << std::endl;
        return false;
    }
    client_print_subscribed(client.getUserId().c_str(), arg.at(0).c_str());
    return true;
}

bool SubscribeCommand::execute(Shell &shell,
    const std::vector<std::string> arg)
{
    return operator ()(shell, arg);
}

std::unique_ptr<IShellCommand> SubscribeCommand::create()
{
    return std::unique_ptr<IShellCommand>(new SubscribeCommand());
}

}
