/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Shell.hpp"
#include "TeamsShell.hpp"
#include "Client.hpp"
#include "Commands/LoginCommand.hpp"
#include "Commands/LogoutCommand.hpp"
#include "Commands/HelpCommand.hpp"
#include "Commands/SendCommand.hpp"
#include "Commands/CreateCommand.hpp"
#include "Commands/InfoCommand.hpp"
#include "Commands/UseCommand.hpp"
#include "Commands/UnsubscribeCommand.hpp"
#include "Commands/UserCommand.hpp"
#include "Commands/MessagesCommand.hpp"
#include "Commands/SubscribeCommand.hpp"
#include "Commands/SubscribedCommand.hpp"
#include "Commands/UsersCommand.hpp"

namespace my_teams::client {

TeamsShell::TeamsShell(Client &client, std::string name,
    std::string prompt):
    Shell::Shell(std::move(name), std::move(prompt)),
    _client(client)
{
    registerCommands();
}

void TeamsShell::registerCommands()
{
    _shellCommandFactory.registerCreator<shell::HelpCommand>("/help");
    _shellCommandFactory.registerCreator<shell::LoginCommand>("/login");
    _shellCommandFactory.registerCreator<shell::LogoutCommand>("/logout");
    _shellCommandFactory.registerCreator<shell::UsersCommand>("/users");
    _shellCommandFactory.registerCreator<shell::UserCommand>("/user");
    _shellCommandFactory.registerCreator<shell::SendCommand>("/send");
    _shellCommandFactory.registerCreator<shell::MessagesCommand>("/messages");
    _shellCommandFactory.registerCreator<shell::SubscribeCommand>("/subscribe");
    _shellCommandFactory.registerCreator<shell::UnsubscribeCommand>("/subscribe");
    _shellCommandFactory.registerCreator<shell::SubscribedCommand>("/subscribed");
    _shellCommandFactory.registerCreator<shell::UseCommand>("/use");
    _shellCommandFactory.registerCreator<shell::CreateCommand>("/create");
    _shellCommandFactory.registerCreator<shell::CreateCommand>("/list");
    _shellCommandFactory.registerCreator<shell::InfoCommand>("/info");

}

void TeamsShell::run()
{
    Shell::run();
}

Client &TeamsShell::getClient() const noexcept
{
    return _client;
}
}
