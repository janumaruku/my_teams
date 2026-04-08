/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MY_TEAMS_SHELL_HPP
#define MY_TEAMS_SHELL_HPP

#include "FactoryTemplate.hpp"
#include "IShellCommand.hpp"
#include "Client.hpp"

namespace my_teams::client {

class Shell {
public:
    using ShellCommandFactory  = designPattern::FactoryTemplate<shell::IShellCommand, std::string>;

    virtual ~Shell() = default;

    Shell();

    explicit Shell(std::string name, std::string prompt, Client client);
    explicit Shell(std::string name, std::string prompt);
    explicit Shell(std::string prompt);

    void run();

protected:
    std::string _name;
    std::string _prompt;
    ShellCommandFactory _shellCommandFactory;
    Client _client;

    virtual bool executeCommand(const std::vector<std::string> &cmd);
};

namespace ShellUtils {

bool isEmptyLine(const std::string &line) noexcept;

std::vector<std::string> split(const std::string &line, const char delim);

}
}

#endif
