/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Acceptor.hpp"
#include "IoContext.hpp"
#include "Router.hpp"
#include "Server.hpp"

int main()
{
    network::Router<int> router{10000};

    router.get("/home", [](auto){});

    router.run();
    // std::string test = "/slkdjf/slkdjf/lsdjkf";
    // auto res = utils::StringUtils::split(test, '/');
    //
    // for (const auto &word: res)
    //     std::cout << word << std::endl;

    return 0;
}
