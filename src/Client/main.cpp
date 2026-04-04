/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** main
*/

#include <memory>

#include "ConnectedSocket.hpp"
#include "IoContext.hpp"

void clientRead(std::shared_ptr<network::ConnectedSocket> sock);

void clientWrite(std::shared_ptr<network::ConnectedSocket> sock);

int main()
{
    network::IOContext ioContext;
    auto sock = std::make_shared<network::ConnectedSocket>(ioContext);
    network::Endpoint endpoint{15000, "127.0.0.1"};
    std::string buffer;
    buffer.resize(1024);

    sock->connect(endpoint);

    clientRead(sock);

    ioContext.run();

    return 0;
}

void clientRead(std::shared_ptr<network::ConnectedSocket> sock)
{
    auto buffer = std::make_shared<std::string>(1024, '\0');

    sock->asyncReadSome(network::Buffer{*buffer},
        [buffer, sock](auto, const std::size_t &len) {
            buffer->resize(len);
            std::cout << "Received from server ..." << std::endl;
            std::cout << *buffer << std::endl;
            clientWrite(sock);
        });
}

void clientWrite(std::shared_ptr<network::ConnectedSocket> sock)
{
    sock->asyncWrite(network::Buffer{"Thanks!!!"},
        [sock](auto, const std::size_t &) {
            std::cout << "Client writing" << std::endl;
            clientRead(sock);
        });
}
