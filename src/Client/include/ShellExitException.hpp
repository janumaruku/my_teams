/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** ShellExit
*/

#ifndef _SHELLEXITEXCEPT_HPP
#define _SHELLEXITEXCEPT_HPP

#include <exception>

namespace my_teams::client::shell {

class ShellExitException: public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "";
    }
};
}

#endif //NANOTEKSPICE_SHELLEXIT_HPP
