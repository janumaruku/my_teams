/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include "Shell.hpp"

namespace my_teams::client::ShellUtils {

bool isEmptyLine(const std::string &line) noexcept
{
    std::stringstream sstream{line};
    std::string temp;

    return !(sstream >> temp);
}

std::vector<std::string> split(const std::string &line, const char delim)
{
    std::stringstream sstream{line};
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(sstream, token, delim)) {
        tokens.push_back(token);
    }

    return tokens;
}

}
