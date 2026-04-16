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
#include "jsonParser.hpp"
#include "Client.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool SendCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    std::cout << "Is helping" << std::endl;
    nlohmann::json req;
    req["method"] = network::Method::POST;
    req["path"] = "/help";
    req["body"] = {};
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    client.send(req.dump(), [](auto, auto){});
    
    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);
    return true;
}

bool SendCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> SendCommand::create()
{
    return std::unique_ptr<IShellCommand>(new SendCommand());
}

}
