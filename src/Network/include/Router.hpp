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
#include "jsonParser.hpp"

namespace network {
enum class Method: uint8_t {
    GET,
    POST,
    PUT,
    DELETE
};

std::ostream &operator<<(std::ostream &stream, const Method &method);

template <typename TClientState>
class Router {
    class Context {
    public:
        Context() = default;

    private:
        nlohmann::json _request;
        std::unordered_map<std::string, std::string> _params;
        TClientState &_state;
    };

    using Handler = std::function<void(Context *)>;

    class RadixTree {
    public:
        struct Node {
            Node();

            explicit Node(const std::string &nodeWord,
                Node *nodeParent = nullptr);

            std::string word;
            Node *parent;
            std::string param;
            std::unique_ptr<Node> paramNode;
            std::unordered_map<std::string, std::unique_ptr<Node>> children;
            Handler handler;
        };

        void add(const std::vector<std::string> &words, Handler handler);

    private:
        std::unordered_map<std::string, std::unique_ptr<Node>> _root;
    };

public:
    explicit Router(const int &port): _acceptor{_ioContext, Endpoint{port}}
    {}

    void run();

    void get(const std::string &path, Handler handler);

private:
    IOContext _ioContext{};
    Acceptor _acceptor;
    std::unordered_map<std::shared_ptr<ConnectedSocket>, TClientState> _clients;
    std::string _readBuffer;
    std::string _writeBuffer;
    std::string _transmission;
    RadixTree _get;

    void startAccept();

    void startClient(const std::shared_ptr<ConnectedSocket> &sock);

    void handleTransmission(TClientState &clientState);

    void handleRead(const size_t &bytes, TClientState &clientState);

    void clientRead(const std::shared_ptr<ConnectedSocket> &sock);

    void clientWrite(const std::shared_ptr<ConnectedSocket> &sock);
};

} // namespace network

#endif // MY_TEAMS_ROUTER_HPP

#include "../RadixTree.tpp"
#include "../Router.tpp"
