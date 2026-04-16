/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Database
*/

#include "Database.hpp"

#include "DBErrorCode.hpp"

namespace liteORM {
Database::Database(const std::string &dbPath): _dbPath{dbPath},
    _tableNotFound{DBErrorCode::TABLE_NOT_FOUND}
{}

Table &Database::table(const std::string &tableName)
{
    if (!_tables.contains(tableName)) {
        return _tableNotFound;
    }

    return _tables.at(tableName);
}
} // liteORM
