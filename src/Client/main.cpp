/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** main
*/

#include "ConnectedSocket.hpp"
#include "IoContext.hpp"

int main()
{
    network::IOContext ioContext;
    network::ConnectedSocket sock{ioContext};
    network::Endpoint endpoint{10000, "127.0.0.1"};
    std::string buffer;
    buffer.resize(1024);

    sock.connect(endpoint);

    sock.asyncReadSome(network::buffer(buffer, buffer.size()),
        [&buffer](auto, const std::size_t &len) {
            buffer.resize(len);
            std::cout << "Received from server ..." << std::endl;
            std::cout << buffer << std::endl;
        });

    ioContext.run();

    return 0;
}
