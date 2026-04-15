/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "LoggingClient.hpp"
#include "Commands/LoginCommand.hpp"
#include "Router.hpp"
#include "jsonParser.hpp"
#include "Serializer.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

bool LoginCommand::operator()(Shell &shell,
    std::vector<std::string> args)
{
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    req["method"] = network::Method::POST;
    req["path"] = "/login";
    req["header"] = {};
    req["body"] = {
			{"username", args.at(0)},
			{"password", ""}
	};
    client.send(req.dump(), [](auto, auto){});

    const std::string jsonString = client.receive();
    Response response = nlohmann::json::parse(jsonString);

    if (response.statusCode != network::StatusCode::STATUS_OK) {
        std::cout << response.body.at("error_message") << std::endl;
        return false;
    }

    User user = response.body;

    client_event_logged_in(user.uuid.c_str(), user.name.c_str());
    return true;
}

bool LoginCommand::execute(Shell &shell,
    const std::vector<std::string> cmd)
{
    return operator ()(shell, cmd);
}

std::unique_ptr<IShellCommand> LoginCommand::create()
{
    return std::unique_ptr<IShellCommand>(new LoginCommand());
}

}
