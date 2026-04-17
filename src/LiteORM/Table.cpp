/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Table
*/

#include "Table.hpp"

#include <fstream>
#include <iostream>

#include "Query.hpp"

namespace liteORM {
Table::Table(const std::string &filePath): _filePath{
    filePath}
{
    load();
}

Table::Table(const std::error_code &err): _error{err}
{}

void Table::setError(const std::error_code &err)
{
    _error = err;
}

std::error_code Table::getError() const noexcept
{
    return _error;
}

const std::string & Table::getName() const noexcept
{
    return _name;
}

Query Table::where(const std::string &condition, const std::string &value)
{
    Query query{*this};

    return query.where(condition, value);
}

bool Table::hasColumn(const std::string &field)
{
    const auto itt = std::ranges::find_if(_json.at("columns"), [field](const auto &item) {
        return item.at("name") == field;
    });

    if (itt == _json.at("columns").end())
        return false;
    return true;
}

const nlohmann::json &Table::getData() const
{
    return _json.at("data");
}

void Table::load()
{
    std::ifstream file{_filePath};

    if (!file.is_open())
        throw std::runtime_error{"DB: Failed to load table"};

    file >> _json;
    _name = _json.at("name").get<std::string>();

    // std::cout << std::setw(2) << _json << std::endl;
}

bool Table::match(const nlohmann::json &entry)
{
    const auto &columns = _json.at("columns");

    for (const auto &column: columns) {
        if (!entry.contains(column.at("name")))
            return false;
    }

    return true;
}
} // liteORM
