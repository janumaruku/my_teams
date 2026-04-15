/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "logging_client.h"
#include "Commands/UsersCommand.hpp"
#include <ostream>
#include "Router.hpp"
#include "jsonParser.hpp"
#include "Serializer.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool UsersCommand::operator()(Shell &shell,
    std::vector<std::string>)
{
    nlohmann::json req;
    req["method"] = network::Method::GET;
    req["path"] = "/home/users";
    req["body"] = {};
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();
 
    client.send(req.dump(), [](auto, auto){});

    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    if (response.statusCode != network::StatusCode::STATUS_OK) {
        std::cout << response.body.at("error_message") << std::endl;
        return false;
    }
    
    std::vector<User> users = response.body;
    for (const auto &user : users) {
        client_print_user(user.uuid.c_str(), user.name.c_str(),
            static_cast<int>(response.statusCode == network::StatusCode::STATUS_OK));
    }
    return true;
}

bool UsersCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> UsersCommand::create()
{
    return std::unique_ptr<IShellCommand>(new UsersCommand());
}

}
