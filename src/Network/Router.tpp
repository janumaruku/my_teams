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
void Router<TClientState>::handleTransmission(TClientState &/*clientState*/)
{
    const nlohmann::json stream = nlohmann::json::parse(_transmission);
    std::cout << std::setw(4) << stream << std::endl;
    const auto temp = stream.at("method").get<Method>();
    std::cout << utils::RED << temp << utils::RESET<< std::endl;
    _transmission.clear();
}

template <typename TClientState>
void Router<TClientState>::handleRead(const size_t &bytes, TClientState &clientState)
{
    _readBuffer.resize(bytes);
    if (_readBuffer.ends_with("\r\n")) {
        _transmission.insert(_transmission.end(), _readBuffer.begin(),
            _readBuffer.end());
        _transmission.pop_back();
        _transmission.pop_back();
        handleTransmission(clientState);
    }
}

template <typename TClientState>
void Router<TClientState>::clientRead(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    _readBuffer.resize(1024);
    sock->asyncReadSome(buffer(_readBuffer, _readBuffer.size()),
        [this, sock](
        const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                return;
            }
            handleRead(bytes, _clients[sock]);
            clientWrite(sock);
        });
}

template <typename TClientState>
void Router<TClientState>::clientWrite(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    nlohmann::json response;
    response["status_code"]    = 200;
    response["status_message"] = "Status OK";
    response["body"]           = {
        {
            {"id", "uuid1"},
            {"name", "Janumaruku"}
        }
    };
    _writeBuffer = response.dump(2);
    sock->asyncWrite(buffer(_writeBuffer),
        [this, sock](
        const std::error_code &err, const std::size_t & /*bytes*/) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            clientRead(sock);
        });
}

inline std::ostream &operator<<(std::ostream &stream, const Method &method)
{
    switch (method) {
    case Method::GET:
        stream << "GET";
        break;
    case Method::POST:
        stream << "POST";
        break;
    case Method::PUT:
        stream << "PUT";
        break;
    case Method::DELETE:
        stream << "DELETE";
        break;
    default:
        break;
    }

    return stream;
}
} // namespace network
