/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Client.hpp"
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
    std::cout << "debub" << std::endl;
    if (args.empty())
        return true;
    nlohmann::json req;
    auto &client = dynamic_cast<TeamsShell &>(shell).getClient();

    std::string username = args.at(0);
    client.setContext(CommandContextType::USER);
    client.setUserId(username);

    req["method"] = network::Method::POST;
    req["path"] = "/login";
    req["header"] = {};
    req["body"] = {
			{"username", username},
			{"password", ""}
	};
    client.send(req.dump());

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
    const std::vector<std::string> args)
{
    return operator ()(shell, args);
}

std::unique_ptr<IShellCommand> LoginCommand::create()
{
    return std::unique_ptr<IShellCommand>(new LoginCommand());
}

}
