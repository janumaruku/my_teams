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
        return "Connection limit reached";
    default:
        return "Unknown error";
    }
}
