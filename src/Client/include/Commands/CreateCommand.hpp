/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
**
*/

#ifndef MYTEAMS_CREATE_HPP
#define MYTEAMS_CREATE_HPP

#include <memory>

#include "Client.hpp"
#include "IShellCommand.hpp"
#include "Serializer.hpp"
#include "TeamsShell.hpp"

namespace my_teams::client::shell {

class CreateCommand: public IShellCommand {
public:
    CreateCommand() = default;

    ~CreateCommand() override = default;

    bool operator()(Shell &shell, std::vector<std::string> arg) override;

    bool execute(Shell &shell, std::vector<std::string> arg) override;

    static std::unique_ptr<IShellCommand> create();

private:
    static void createTeam(nlohmann::json &req, const Client &client,
        const std::vector<std::string> &args);

    static void createChannel(nlohmann::json &req, const Client &client,
        const std::vector<std::string> &args);

    static void createThread(nlohmann::json &req, const Client &client,
        const std::vector<std::string> &args);

    static void createComment(nlohmann::json &req, const Client &client,
        const std::vector<std::string> &args);

    static void createLog(const CommandContextType &context, const Response &response);
};

} // namespace my_teams::client::shell
#endif
