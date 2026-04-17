/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Query
*/

#include "include/Query.hpp"

#include "DBErrorCode.hpp"
#include "Options.hpp"
#include "StringUtils.hpp"

namespace liteORM {
Query::Query(Table &table): _table{table}
{}

Query &Query::where(const std::string &condition, const std::string &value)
{
    if (!_table.getError()) {
        _error = _table.getError();
        return *this;
    }

    std::string tempCondition = condition;
    std::erase_if(tempCondition, isspace);
    if (!tempCondition.ends_with("=?")) {
        _error = DBErrorCode::INVALID_QUERY;
        return *this;
    }

    const auto words = utils::StringUtils::split(tempCondition, '=');

    _conditions.emplace_back(words[0], value);

    return *this;
}
} // liteORM
