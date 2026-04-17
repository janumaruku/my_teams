/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Database
*/

#ifndef MY_TEAMS_DATABASE_HPP
#define MY_TEAMS_DATABASE_HPP

#include <string>

#include "Table.hpp"

namespace liteORM {

class Database {
public:
    explicit Database(const std::string &dbPath);

    Table &table(const std::string &tableName);

private:
    std::string _dbPath;
    std::unordered_map<std::string, Table> _tables;
    Table _tableNotFound;

    void loadDB();
};

} // liteORM

#endif //MY_TEAMS_DATABASE_HPP
