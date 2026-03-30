/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Acceptor.hpp"
#include "IoContext.hpp"

void acceptClient(network::Acceptor &acceptor)
{
    acceptor.asyncAccept(
        [&acceptor](const std::error_code &err,
            const std::shared_ptr<network::ConnectedSocket> &sock) {
            if (err) {
                std::cerr << err.message() << std::endl;
                acceptClient(acceptor);
            } else {
                sock->syncWrite(
                    network::Buffer{"Wellcome !!!"}, [](auto, auto) {});
                acceptClient(acceptor);
            }
        });
}

int main()
{
    network::IOContext ioContext;
    network::Acceptor acceptor{ioContext, network::Endpoint{15000}};
    acceptClient(acceptor);

    ioContext.run();
}
