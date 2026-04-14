/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Context
*/

#pragma once

#include "Router.tpp"

namespace network {
template <typename TClientState>
Router<TClientState>::Context::Context(nlohmann::json request,
    TClientState &state, ConnectedSocket *socket): _request{std::move(request)},
    _state{state}, _socket{socket}
{}

template <typename TClientState> std::string Router<
    TClientState>::Context::path() const
{
    return _request.at("path").get<std::string>();
}

template <typename TClientState>
void Router<TClientState>::Context::abortWithStatus(const StatusCode &code)
{
    _response["status_code"]    = code;
    _response["status_message"] = STATUES.at(code);
    _response["body"]           = {};
}

template <typename TClientState>
void Router<TClientState>::Context::jsonp(const StatusCode &code,
    const nlohmann::json &body)
{
    _response["status_code"]    = code;
    _response["status_message"] = STATUES.at(code);
    _response["body"]           = body;
}

template <typename TClientState>
const nlohmann::json &Router<TClientState>::Context::response() const noexcept
{
    return _response;
}
} // namespace network
