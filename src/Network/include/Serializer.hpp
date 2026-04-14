/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/


#ifndef MY_TEAMS_SERIALIZER_HPP
#define MY_TEAMS_SERIALIZER_HPP

#include "jsonParser.hpp"
#include "Router.hpp"

using Request = struct Request {
    network::Method method;
    std::string path;
    nlohmann::json body;
};

using Response = struct Response {
    int statusCode;
    std::string statusMessage;
    nlohmann::json body;
};

namespace nlohmann {

template<>
struct adl_serializer<Request> {

    static void to_json(json &j, Request &r);
    static void from_json(const json &j, Request &r);
};

template<>
struct adl_serializer<Response> {

    static void to_json(json &j, Response &r);
    static void from_json(const json &j, Response &r);
};

}

#endif
