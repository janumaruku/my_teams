/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Table
*/

#ifndef MY_TEAMS_TABLE_HPP
#define MY_TEAMS_TABLE_HPP
#include <iostream>
#include <string>

#include "constants.hpp"
#include "DBErrorCode.hpp"
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

    template <typename T>
    std::error_code create(const T &entry)
    {
        nlohmann::json jEntry;

        try {
            jEntry = entry;
            if (!match(jEntry))
                return DBErrorCode::TYPE_MISMATCH;
        } catch (const std::exception &e) {
            std::cout << "JSON error: " << utils::RED << e.what() <<
                utils::RESET << std::endl;
            return DBErrorCode::TYPE_MISMATCH;
        }

        _json.at("data").push_back(jEntry);
        return {};
    }

    bool hasColumn(const std::string &field);

    const nlohmann::json &getData() const;

private:
    std::string _filePath;
    std::string _name;
    nlohmann::json _json;
    std::error_code _error;

    void load();

    bool match(const nlohmann::json &entry);
};
}

#endif //MY_TEAMS_TABLE_HPP
