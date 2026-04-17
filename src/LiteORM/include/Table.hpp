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
class Query;

class Table {
public:
    explicit Table(const std::string &filePath);

    explicit Table(const std::error_code &err);

    void setError(const std::error_code &err);

    [[nodiscard]] std::error_code getError() const noexcept;

    [[nodiscard]] const std::string &getName() const noexcept;

    Query where(const std::string &condition, const std::string &value);

private:
    std::string _filePath;
    std::string _name;
    nlohmann::json _json;
    std::error_code _error;

    void load();
};
}

#endif //MY_TEAMS_TABLE_HPP
