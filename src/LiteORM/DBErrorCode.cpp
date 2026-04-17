/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DBErrorCode
*/

#include "DBErrorCode.hpp"

const char * DBErrorCodeCategory::name() const noexcept
{
    return "DB error code";
}

std::string DBErrorCodeCategory::message(int errorValue) const
{

    switch (static_cast<DBErrorCode>(errorValue)) {
    case DBErrorCode::TABLE_NOT_FOUND:
        return "Table not found";
    case DBErrorCode::INVALID_QUERY:
        return "Invalid query";
    case DBErrorCode::NOT_FOUND:
        return "Resource not found";
    case DBErrorCode::TYPE_MISMATCH:
        return "Type mismatch";
    case DBErrorCode::UNKNOWN_FIELD:
        return "Unknown field";
    default:
        return "Unknown error";
    }
}

std::error_condition DBErrorCodeCategory::default_error_condition(
    int errorValue) const noexcept
{
    return {errorValue, *this};
}

std::error_code make_error_code(DBErrorCode errCode) noexcept
{
    return {static_cast<int>(errCode), dbCategory()};
}
