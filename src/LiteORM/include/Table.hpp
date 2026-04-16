/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Table
*/

#ifndef MY_TEAMS_TABLE_HPP
#define MY_TEAMS_TABLE_HPP
#include <string>

#include "Serializer.hpp"

namespace liteORM {
class Table {
public:
    explicit Table(const std::string &name, const std::string &filePath);

    explicit Table(const std::error_code &err);

    void setError(const std::error_code &err);

private:
    std::string _filePath;
    std::string _name;
    nlohmann::json _json;
    std::error_code _error;

    void load();
};
}

#endif //MY_TEAMS_TABLE_HPP
