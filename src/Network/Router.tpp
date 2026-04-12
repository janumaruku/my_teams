/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router
*/

#pragma once

#include "Router.hpp"
#include "StringUtils.hpp"
#include "jsonParser.hpp"

namespace network {
template <typename TClientState>
void Router<TClientState>::run()
{
    startAccept();
    _ioContext.run();
}

template <typename TClientState>
void Router<TClientState>::get(const std::string &path, Handler handler)
{
    const auto splitPath = utils::StringUtils::split(path, '/');
    _get.add(splitPath, handler);
}

template <typename TClientState>
void Router<TClientState>::startAccept()
{
    _acceptor.asyncAccept([this](const std::error_code &err,
        const std::shared_ptr<ConnectedSocket> &sock) {
            if (err) {
                std::cerr << err.message() << std::endl;
            } else {
                _clients[sock] = {};
                startClient(sock);
            }
            startAccept();
        });
}

template <typename TClientState>
void Router<TClientState>::startClient(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    clientRead(sock);
}

template <typename TClientState>
void Router<TClientState>::handleTransmission()
{
    // const nlohmann::json stream = nlohmann::json::parse(_transmission);
    std::cout << _transmission << std::endl;
    _transmission.clear();
}

template <typename TClientState>
void Router<TClientState>::handleRead(const size_t &bytes)
{
    _readBuffer.resize(bytes);
    if (_readBuffer.ends_with("\r\n")) {
        _transmission.insert(_transmission.end(), _readBuffer.begin(),
            _readBuffer.end());
        _transmission.pop_back();
        _transmission.pop_back();
        _transmission.push_back('\n');
        handleTransmission();
    }
}

template <typename TClientState>
void Router<TClientState>::clientRead(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    auto readBuffer = std::make_shared<std::string>(1024, '\0');
    
    sock->asyncReadSome(buffer(*readBuffer, readBuffer->size()),
        [this, sock, readBuffer](
        const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                return;
            }
            readBuffer->resize(bytes);
            std::cout << *readBuffer << std::endl;
            clientWrite(sock);
        });
}

template <typename TClientState>
void Router<TClientState>::clientWrite(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    sock->asyncWrite(buffer("Hello!!!"),
        [this, sock](
        const std::error_code &err, const std::size_t & /*bytes*/) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            clientRead(sock);
        });
}
} // namespace network
