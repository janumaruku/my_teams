/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MY_TEAMS_SHELL_HPP
#define MY_TEAMS_SHELL_HPP

#include <string>
#include "FactoryTemplate.hpp"
#include "IShellCommand.hpp"
#include "Client.hpp"

namespace my_teams::client {

constexpr std::string EXIT_PROMPT = "exit";
constexpr std::string BASE_NAME = "default_shell";
constexpr std::string BASE_PROMPT= "> ";


class Shell {
public:
    using ShellCommandFactory  = designPattern::FactoryTemplate<shell::IShellCommand, std::string>;

    virtual ~Shell() = default;

    Shell() noexcept;

    explicit Shell(const Client &client, std::string name, std::string prompt) noexcept;
    explicit Shell(std::string name, std::string prompt) noexcept;
    explicit Shell(std::string prompt) noexcept;

    void run();

protected:
    std::string _name;
    std::string _prompt;
    ShellCommandFactory _shellCommandFactory;
    std::unique_ptr<Client> _client;
    bool executeCommand(const std::vector<std::string> &cmd);
    void registerCommands();
};

namespace ShellUtils {

bool isEmptyLine(const std::string &line) noexcept;

std::vector<std::string> split(const std::string &line, const char delim);

}
}

#endif
