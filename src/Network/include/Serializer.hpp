/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MY_TEAMS_SERIALIZER_HPP
#define MY_TEAMS_SERIALIZER_HPP

#include "jsonParser.hpp"
#include "../../Types/Types.hpp"

namespace network {
enum class Method: uint8_t {
    GET,
    POST,
    PUT,
    DELETE
};

enum class StatusCode: uint16_t {
    STATUS_OK          = 200,
    UNAUTHORIZED       = 401,
    NOT_FOUND          = 404,
    METHOD_NOT_ALLOWED = 405
};
}

using Request = struct Request {
    network::Method method;
    std::string path;
    nlohmann::json body;
};

using Response = struct Response {
    network::StatusCode statusCode;
    std::string statusMessage;
    nlohmann::json body = {};
};


namespace nlohmann {

template<>
struct adl_serializer<Timestamp> {
    static void to_json(json &j, const Timestamp &t);
    static void from_json(const json &j, Timestamp &t);
};

template<>
struct adl_serializer<Request> {
    static void to_json(json &j, const Request &r);
    static void from_json(const json &j, Request &r);
};

template<>
struct adl_serializer<Response> {
    static void to_json(json &j, const Response &r);
    static void from_json(const json &j, Response &r);
};

template<>
struct adl_serializer<Team> {
    static void to_json(json &j, const Team &t);
    static void from_json(const json &j, Team &t);
};

template<>
struct adl_serializer<Channel> {
    static void to_json(json &j, const Channel &c);
    static void from_json(const json &j, Channel &c);
};

template<>
struct adl_serializer<Thread> {
    static void to_json(json &j, const Thread &t);
    static void from_json(const json &j, Thread &t);
};

template<>
struct adl_serializer<Subscription> {
    static void to_json(json &j, const Subscription &s);
    static void from_json(const json &j, Subscription &s);
};

template<>
struct adl_serializer<Comment> {
    static void to_json(json &j, const Comment &c);
    static void from_json(const json &j, Comment &c);
};

template<>
struct adl_serializer<User> {
    static void to_json(json &j, const User &u);
    static void from_json(const json &j, User &u);
};

template<>
struct adl_serializer<Message> {
    static void to_json(json &j, const Message &m);
    static void from_json(const json &j, Message &m);
};

}

#endif
