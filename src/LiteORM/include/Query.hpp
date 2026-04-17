/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Query
*/

#ifndef MY_TEAMS_QUERY_HPP
#define MY_TEAMS_QUERY_HPP

#include <iostream>

#include "constants.hpp"
#include "DBErrorCode.hpp"
#include "Options.hpp"
#include "Table.hpp"
#include "Types.hpp"

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
    std::error_code first(T &result)
    {
        if (_error)
            return _error;

        if (!hasColumns())
            return _error;

        const nlohmann::json &data = _table.getData();
        nlohmann::json filtered    = applyCondition(data, _conditions.front());
        _conditions.erase(_conditions.begin(), _conditions.begin());

        if (!_conditions.empty()) {
            for (const auto &condition: _conditions)
                filtered = applyCondition(filtered, condition);
        }

        try {
            if (filtered.empty())
                return DBErrorCode::NOT_FOUND;
            result = filtered.front().get<T>();
        } catch (const std::exception &e) {
            std::cout << "JSON error: " << utils::RED << e.what() <<
                utils::RESET << std::endl;
            return DBErrorCode::TYPE_MISMATCH;
        }

        return {};
    }

    template <typename T>
    std::error_code find(T &results)
    {
        if (_error)
            return _error;

        if (!hasColumns())
            return _error;

        const nlohmann::json &data = _table.getData();
        nlohmann::json filtered    = applyCondition(data, _conditions.front());
        _conditions.erase(_conditions.begin(), _conditions.begin());

        if (!_conditions.empty()) {
            for (const auto &condition: _conditions)
                filtered = applyCondition(filtered, condition);
        }

        try {
        if (filtered.empty())
            return DBErrorCode::NOT_FOUND;
        results = filtered.get<T>();
        } catch (const std::exception &e) {
            std::cout << "JSON error: " << utils::RED << e.what() <<
                utils::RESET << std::endl;
            return DBErrorCode::TYPE_MISMATCH;
        }

        return {};
    }

private:
    Table &_table;
    std::vector<Condition> _conditions;
    std::error_code _error;

    // bool match(const nlohmann::json &/*item*/)
    // {
    //     return false;
    // }

    bool hasColumns() noexcept;

    nlohmann::json applyCondition(const nlohmann::json &data,
        const Condition &condition);
};

} // namespace liteORM

#endif // MY_TEAMS_QUERY_HPP
