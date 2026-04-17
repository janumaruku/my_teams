/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DBErrorCode
*/

#ifndef MY_TEAMS_DB_ERROR_CODE_HPP
#define MY_TEAMS_DB_ERROR_CODE_HPP

#include <cstdint>
#include <system_error>
#include <type_traits>

enum class DBErrorCode : uint8_t {
    TABLE_NOT_FOUND = 1,
    INVALID_QUERY,
    NOT_FOUND,
    TYPE_MISMATCH,
    UNKNOWN_FIELD,
};

template <> struct std::is_error_code_enum<DBErrorCode>: true_type {};

struct DBErrorCodeCategory: std::error_category {
    [[nodiscard]] const char *name() const noexcept override;

    [[nodiscard]] std::string message(int errorValue) const override;

    std::error_condition
        default_error_condition(int errorValue) const noexcept override;
};

inline const DBErrorCodeCategory &dbCategory() noexcept
{
    static const DBErrorCodeCategory category{};

    return category;
}

std::error_code make_error_code(DBErrorCode errCode) noexcept; // NOLINT

#endif //MY_TEAMS_DB_ERROR_CODE_HPP
