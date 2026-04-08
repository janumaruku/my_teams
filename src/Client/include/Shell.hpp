/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MY_TEAMS_SHELL_HPP
#define MY_TEAMS_SHELL_HPP

#include "../DesignPattern/FactoryTemplate.hpp"
#include "IShellCommand.hpp"

namespace myteams::client::shell {

class Shell {
public:
    using ShellCommandFactory  = FactoryTemplate<IShellCommand, std::string>;

    virtual ~Shell() = default;

    Shell();


    explicit Shell(std::string name, std::string prompt);
    explicit Shell(std::string prompt);

    void run();

protected:
    std::string _name;
    std::string _prompt;
    ShellCommandFactory _shellCommandFactory;

    virtual bool executeCommand(const std::vector<std::string> &cmd);
};

}

#endif
