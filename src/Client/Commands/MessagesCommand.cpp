/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <functional>
#include "Commands/MessagesCommand.hpp"
#include "Router.hpp"
#include "Serializer.hpp"
#include "Types.hpp"
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"
#include "logging_client.h"

namespace my_teams::client::shell {

bool MessagesCommand::operator()(Shell &shell,
    std::vector<std::string> args)
{
    nlohmann::json req;
    req["method"] = network::Method::GET;
    req["path"] = "/home/users/" + args.at(0) + "/messages";
    req["body"] = {};
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);
    std::vector<Message> messages = response.body;
    for (const auto &message : messages) {
        client_private_message_print_messages(message.senderId.c_str(),
            std::chrono::system_clock::to_time_t(message.createdAt),
            message.content.c_str());
    }
    return true;
}

bool MessagesCommand::execute(Shell &shell,
    const std::vector<std::string> args)
{
    return operator ()(shell, args);
}

std::unique_ptr<IShellCommand> MessagesCommand::create()
{
    return std::unique_ptr<IShellCommand>(new MessagesCommand());
}

}
