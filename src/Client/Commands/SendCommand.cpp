/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "LoggingClient.hpp"
#include "Commands/SendCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"
#include "Types.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool SendCommand::operator()(Shell &shell,
    std::vector<std::string> arg)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
    req["method"] = network::Method::POST;
    req["path"] = "/home/users/" +  client.getUserId() + "/message";
    req["body"].at("send_to") = arg.at(0); 
    req["body"].at("message") = arg.at(1); 
    
    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);
    Message message = response.body.get<Message>();

    client_event_private_message_received(message.senderId.c_str(), message.content.c_str());
    return true;
}

bool SendCommand::execute(Shell &shell,
    const std::vector<std::string> arg)
{
    return operator ()(shell, arg);
}

std::unique_ptr<IShellCommand> SendCommand::create()
{
    return std::unique_ptr<IShellCommand>(new SendCommand());
}

}
