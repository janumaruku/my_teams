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
    class Context {
    public:
        Context() = default;

    private:
        std::unordered_map<std::string, std::string> _params;
        TClientState _state;
    };

    using Handler = std::function<void(Context *)>;

    class RadixTree {
    public:
        struct Node {
            std::string word;
            Node *parent;
            std::pair<std::string, Node *> param;
            std::unordered_map<std::string, Node *> children;
            Handler handler;
        };
    };

public:
    explicit Router(const int &port): _acceptor{_ioContext, Endpoint{port}}
    {}

    void run();

private:
    IOContext _ioContext{};
    Acceptor _acceptor;
    std::unordered_map<std::shared_ptr<ConnectedSocket>, TClientState> _clients;
    std::string _readBuffer;

    void startAccept();

    void startClient(const std::shared_ptr<ConnectedSocket> &sock);

    void clientRead(const std::shared_ptr<ConnectedSocket> &sock);

    void clientWrite(const std::shared_ptr<ConnectedSocket> &sock);
};

} // namespace network

#endif // MY_TEAMS_ROUTER_HPP

#include "../Router.tpp"
