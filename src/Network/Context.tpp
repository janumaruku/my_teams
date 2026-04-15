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
{
    _middlewares.emplace_back([this](Context *) {
        next();
    });
}

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

template <typename TClientState>
void Router<TClientState>::Context::addMiddleware(const Handler &middleware)
{
    _middlewares.push_back(middleware);

    if (!_middlewares.empty())
        _currentHandler = _middlewares.begin();
}

template <typename TClientState>
void Router<TClientState>::Context::addMiddlewares(
    const std::vector<Handler> &middlewares)
{
    _middlewares.insert(_middlewares.end(), middlewares.begin(),
        middlewares.end());

    if (!_middlewares.empty())
        _currentHandler = _middlewares.begin();
}

template <typename TClientState>
void Router<TClientState>::Context::addHandler(const Handler &handler)
{
    _middlewares.push_back(handler);
}

template <typename TClientState>
void Router<TClientState>::Context::addHandlers(
    const std::vector<Handler> &handlers)
{
    _handlers.insert(_handlers.end(), handlers.begin(), handlers.end());
}

template <typename TClientState>
void Router<TClientState>::Context::addParams(
    const std::vector<std::pair<std::string, std::string>> &params)
{
    for (const auto &[key, value]: params)
        _params[key] = value;
}

template <typename TClientState>
void Router<TClientState>::Context::next()
{
    ++_currentHandler;
    if (_currentHandler != _middlewares.end()) {
        (*_currentHandler)(this);
    } else {
        for (const auto &handler: _handlers)
            handler(this);
    }
}

template <typename TClientState>
bool Router<TClientState>::Context::hasHandlers() const noexcept
{
    return _handlers.empty();
}
} // namespace network
