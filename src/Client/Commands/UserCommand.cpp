/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <ostream>
#include "LoggingClient.hpp"
#include "Commands/UserCommand.hpp"
#include "Router.hpp"
#include "jsonParser.hpp"
#include "Serializer.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool UserCommand::operator()(Shell &shell,
    std::vector<std::string> arg)
{
    nlohmann::json req;
    req["method"] = network::Method::GET;
    req["path"] = "/home/users/" + arg.at(0);
    req["body"] = {};
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
 
    client.send(req.dump(), [](auto, auto){});

    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    if (response.statusCode != network::StatusCode::STATUS_OK) {
        std::cout << response.body.at("error_message") << std::endl;
        return false;
    }
    User user = response.body;
    client_print_user(user.uuid.c_str(), user.name.c_str(),
        static_cast<int>(response.statusCode == network::StatusCode::STATUS_OK));
    return true;
}

bool UserCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> UserCommand::create()
{
    return std::unique_ptr<IShellCommand>(new UserCommand());
}

}
