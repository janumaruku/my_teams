/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Table
*/

#include "Table.hpp"

#include <fstream>

namespace liteORM {
Table::Table(const std::string &name, const std::string &filePath): _filePath{
    filePath}, _name{name}
{
    load();
}

void Table::load()
{
    std::ifstream file{_filePath};

    if (!file.is_open())
        throw std::runtime_error{"DB: Failed to load table"};

    file >> _json;
}
} // liteORM
