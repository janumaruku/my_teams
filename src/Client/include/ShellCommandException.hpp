/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** ShellExit
*/

#ifndef MYTEAMS_SHELLCMDEXCEPT_HPP
#define MYTEAMS_SHELLCMDEXCEPT_HPP
#include <exception>
#include <string>
#include <utility>

namespace my_teams::client::shell {

class ShellCommandException: public std::exception {
public:
    ShellCommandException(std::string what) : _what(std::move(what)) {}
    [[nodiscard]] const char *what() const noexcept override {
        return _what.c_str();
    }
private:
    std::string _what;
};
}

#endif //MYTEAMS_SHELLCMDEXCEPT_HPP
