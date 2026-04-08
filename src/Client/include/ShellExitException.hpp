/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** ShellExit
*/

#ifndef NANOTEKSPICE_SHELLEXIT_HPP
#define NANOTEKSPICE_SHELLEXIT_HPP

#include <exception>
#include <memory>
#include "IShellCommand.hpp"
#include "Shell.hpp"

namespace my_teams::client::shell {

class ShellExitException: public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "";
    }
};
}

// #include "../src/ShellExit.tpp"

#endif //NANOTEKSPICE_SHELLEXIT_HPP
