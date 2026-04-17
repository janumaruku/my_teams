/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Database
*/

#ifndef MY_TEAMS_DATABASE_HPP
#define MY_TEAMS_DATABASE_HPP
#include <string>

namespace liteORM {

class Database {
public:
    explicit Database(const std::string &dbPath);

private:
    std::string _dbPath;
};

} // liteORM

#endif //MY_TEAMS_DATABASE_HPP
