/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router
*/

#pragma once

#include "Router.hpp"

namespace network {
template <typename TClientState>
void Router<TClientState>::run()
{
    startAccept();
    _ioContext.run();
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
void Router<TClientState>::clientRead(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    _readBuffer.resize(1024);
    sock->asyncReadSome(buffer(_readBuffer, _readBuffer.size()),
        [this, sock](
        const std::error_code &err, const std::size_t & /*bytes*/) {
            if (err) {
                std::cerr << err.message() << std::endl;
                clientRead(sock);
            } else {
                clientWrite(sock);
            }
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
