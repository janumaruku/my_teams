/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Query
*/

#ifndef MY_TEAMS_QUERY_HPP
#define MY_TEAMS_QUERY_HPP

#include "Table.hpp"

namespace liteORM {

class Query {
    struct Condition {
        std::string field;
        std::string value;
    };

public:
    explicit Query(Table &table);

    Query &where(const std::string &condition, const std::string &value);

    template <typename T>
    bool first(T &/*result*/){return false;}

    template <typename T>
    void find(std::vector<T> &/*results*/){}

private:
    Table &_table;
    std::vector<Condition> _conditions;
    std::error_code _error;

    bool match(const nlohmann::json &/*item*/){return false;}
};

} // namespace liteORM

#endif // MY_TEAMS_QUERY_HPP
