/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include <string>
#include "Acceptor.hpp"
#include "Client.hpp"
#include "Database.hpp"
#include "IoContext.hpp"
#include "Query.hpp"
#include "Router.hpp"
#include "Server.hpp"
#include <uuid/uuid.h>

int main(int /*ac*/, char **/*av*/)
{
    // if (ac < 2)
    //     return EXIT_EPITECH;
    //
    // try {
    //     const int port = std::stoi(av[1]);
    //     my_teams::server::Server server{port};
    //
    //     server.run();
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    //     return EXIT_EPITECH;
    // }


    uuid_t uuid;
    char uuid_str[37]; // 36 chars + null terminator

    uuid_generate(uuid);              // generate UUID
    uuid_unparse(uuid, uuid_str);     // convert to string

    printf("UUID: %s\n", uuid_str);

    return 0;
}
