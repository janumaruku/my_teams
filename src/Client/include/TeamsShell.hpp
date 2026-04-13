/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MY_TEAMSTSHELL_HPP
#define MY_TEAMSTSHELL_HPP

#include "Shell.hpp"
#include "Client.hpp"

namespace my_teams::client {

class TeamsShell : public Shell {
public:
    using ShellCommandFactory  = designPattern::FactoryTemplate<shell::IShellCommand, std::string>;

    ~TeamsShell() override = default;

    TeamsShell();

    explicit TeamsShell(const Client &client, std::string name, std::string prompt);
    explicit TeamsShell(std::string name, std::string prompt);
    explicit TeamsShell(std::string prompt);

    Client *getClient() const noexcept;

    void run();

private:
    std::unique_ptr<Client> _client;
    void registerCommands();
};

}
#endif
