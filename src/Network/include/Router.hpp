/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router
*/

#ifndef MY_TEAMS_ROUTER_HPP
#define MY_TEAMS_ROUTER_HPP

#include "Acceptor.hpp"
#include "IoContext.hpp"

namespace network {
template <typename TClientState>
class Router {
public:
    explicit Router(const int &port): _acceptor{_ioContext, Endpoint{port}}
    {}

    void run()
    {
        startAccept();
        _ioContext.run();
    }

private:
    IOContext _ioContext{};
    Acceptor _acceptor;
    std::unordered_map<std::shared_ptr<ConnectedSocket>, TClientState> _clients;
    std::string _readBuffer;

    void startAccept()
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

    void startClient(const std::shared_ptr<ConnectedSocket> &sock)
    {
        clientRead(sock);
    }

    void clientRead(const std::shared_ptr<ConnectedSocket> &sock)
    {
        _readBuffer.resize(1024);
        sock->asyncReadSome(buffer(_readBuffer, _readBuffer.size()),
            [this, sock](const std::error_code &err, const std::size_t &/*bytes*/) {
                if (err) {
                    std::cerr << err.message() << std::endl;
                    clientRead(sock);
                } else {
                    clientWrite(sock);
                }
            });
    }

    void clientWrite(const std::shared_ptr<ConnectedSocket> &sock)
    {
        sock->asyncWrite(buffer("Hello!!!"),
            [this, sock](const std::error_code &err, const std::size_t &/*bytes*/) {
               if (err) {
                   std::cerr << err.message() << std::endl;
               }
                clientRead(sock);
            });
    }
};

} // namespace network

#endif // MY_TEAMS_ROUTER_HPP
