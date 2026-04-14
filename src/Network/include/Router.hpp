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

enum class StatusCode: uint16_t {
    STATUS_OK    = 200,
    UNAUTHORIZED = 401,
    NOT_FOUND    = 404
};

const std::unordered_map<StatusCode, std::string> STATUES = {
    {StatusCode::STATUS_OK, "Status OK"},
    {StatusCode::UNAUTHORIZED, "Unauthorised"},
    {StatusCode::NOT_FOUND, "Not Found"}
};

std::ostream &operator<<(std::ostream &stream, const Method &method);

template <typename TClientState>
class Router {
public:
    class Context {
    public:
        Context(nlohmann::json request, TClientState &state,
            ConnectedSocket *socket);

        std::string path() const;

        void abortWithStatus(const StatusCode &code);

        const nlohmann::json &response() const noexcept;

    private:
        nlohmann::json _request;
        nlohmann::json _response;
        std::unordered_map<std::string, std::string> _params;
        TClientState &_state;
        ConnectedSocket *_socket;
    };

private:
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
            std::unique_ptr<Node> paramNode = nullptr;
            std::unordered_map<std::string, std::unique_ptr<Node>> children;
            std::vector<Handler> handlers;
            bool isPath = false;
        };

        void add(const std::vector<std::string> &words,
            std::initializer_list<Handler> handlers);

        void handle(Context &context);

        const std::unordered_map<std::string, std::unique_ptr<Node>> &
        getRoot() const
        {
            return _root;
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<Node>> _root;

        Node *find(const std::vector<std::string> &words);
    };

public:
    explicit Router(const int &port): _acceptor{_ioContext, Endpoint{port}}
    {}

    void run();

    void get(const std::string &path, std::initializer_list<Handler> handlers);

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

    void handleTransmission(ConnectedSocket *socket, TClientState &clientState);

    void handleRead(const size_t &bytes, ConnectedSocket *socket,
        TClientState &clientState);

    void clientRead(ConnectedSocket *sock);

    void clientWrite(ConnectedSocket *sock, const std::string &message);
};

} // namespace network

#endif // MY_TEAMS_ROUTER_HPP

#include "../Context.tpp"
#include "../RadixTree.tpp"
#include "../Router.tpp"
