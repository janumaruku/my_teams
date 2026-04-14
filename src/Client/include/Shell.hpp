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
#include "Commands/IShellCommand.hpp"

namespace my_teams::client {

constexpr std::string EXIT_PROMPT = "exit";
constexpr std::string BASE_NAME = "default_shell";
constexpr std::string BASE_PROMPT= "> ";

class Shell {
public:
    using ExternCommandFactory = designPattern::FactoryTemplate<shell::IShellCommand, std::string>;
    using ShellCommandFactory  = designPattern::FactoryTemplate<shell::IShellCommand, std::string>;

    Shell();

    virtual ~Shell() = default;

    explicit Shell(std::string name, std::string prompt);

    explicit Shell(std::string prompt);

    void run();

protected:
    std::string _name;
    std::string _prompt;
    ShellCommandFactory _shellCommandFactory;

    virtual bool executeCommand(const std::vector<std::string> &cmd);
};
namespace ShellUtils {

bool isEmptyLine(const std::string &line) noexcept;

std::vector<std::string> split(const std::string &line, const char &delim);

}
}

#endif
