/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Database
*/

#include "Database.hpp"

#include <filesystem>

#include "DBErrorCode.hpp"

namespace  fs = std::filesystem;

namespace liteORM {
Database::Database(const std::string &dbPath): _dbPath{dbPath},
    _tableNotFound{DBErrorCode::TABLE_NOT_FOUND}
{
    loadDB();
}

Table &Database::table(const std::string &tableName)
{
    if (!_tables.contains(tableName)) {
        return _tableNotFound;
    }

    return _tables.at(tableName);
}

void Database::loadDB()
{
    const fs::path directory{_dbPath};

    if (!fs::is_directory(directory))
        throw std::runtime_error{"Error: db directory not found"};

    for (const auto &entry: fs::directory_iterator(directory)) {
        Table table{entry.path().string()};
        _tables.emplace(table.getName(), std::move(table));
    }
}
} // liteORM
