/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Acceptor.hpp"
#include "IoContext.hpp"

void acceptClient(network::Acceptor &acceptor);

void clientSessionWrite(std::shared_ptr<network::ConnectedSocket> sock);

void clientSessionRead(std::shared_ptr<network::ConnectedSocket> sock);

int main()
{
    network::IOContext ioContext;
    network::Acceptor acceptor{ioContext, network::Endpoint{15000}};
    acceptClient(acceptor);

    ioContext.run();
}

void acceptClient(network::Acceptor &acceptor)
{
    acceptor.asyncAccept(
        [&acceptor](const std::error_code &err,
        const std::shared_ptr<network::ConnectedSocket> &sock) {
            if (err) {
                std::cerr << err.message() << std::endl;
                acceptClient(acceptor);
            } else {
                clientSessionWrite(sock);
                acceptClient(acceptor);
            }
        });
}

void clientSessionWrite(std::shared_ptr<network::ConnectedSocket> sock)
{
    sock->asyncWrite(network::Buffer{"Wellcome !!!"},
        [sock](auto, auto) {
            std::cout << "Server writing" << std::endl;
            clientSessionRead(sock);
        });
}

void clientSessionRead(std::shared_ptr<network::ConnectedSocket> sock)
{
    auto buffer = std::make_shared<std::string>(1024, '\0');

    sock->asyncReadSome(network::Buffer{*buffer},
        [buffer, sock](auto, const std::size_t &len) {
            buffer->resize(len);
            std::cout << *buffer << std::endl;
            clientSessionWrite(sock);
        });
}
