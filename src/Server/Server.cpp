/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

#include <uuid/uuid.h>

#include "Query.hpp"

namespace my_teams {
namespace server {
Server::Server(const int &port): _router{port}, _db{"db"}
{}

void Server::run()
{
    _router.get("/home", {clientHelp(_db)});
    _router.post("/login", {clientLogin(_db)});

    _router.run();
}

std::string Server::generateUuid() noexcept
{
    uuid_t uuid;
    char uuidStr[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuidStr);

    return std::string{uuidStr};
}

Server::Handler Server::clientHelp(liteORM::Database &)
{
    return [](network::Router<UserState>::Context *ctx) {
        nlohmann::json body;
        body["message"] = "Help message";
        ctx->jsonp(network::StatusCode::STATUS_OK, body);
    };
}

Server::Handler Server::clientLogin(liteORM::Database &database)
{
    return [&database](network::Router<UserState>::Context *ctx) {
        User user;
        const auto err = database.table("user").where("name = ?",
            ctx->getRequest().body.at("username")).first(user);
        if (err) {
            user.uuid = generateUuid();
            user.name = ctx->getRequest().body.at("username");
            user.createdAt = std::chrono::system_clock::now();
            user.updatedAt = std::chrono::system_clock::now();
        }
        UserState &temp = ctx->getClientState();
        temp.user = user;
        temp.isLoggedIn = true;

        ctx->jsonp(network::StatusCode::STATUS_OK, user);
    };
}
} // server
} // my_teams
