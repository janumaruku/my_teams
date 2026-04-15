/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <exception>
#include <format>
#include <string>
#include "Serializer.hpp"

namespace nlohmann {
void adl_serializer<Timestamp>::to_json(json &j, const Timestamp &t)
{
    j = std::format("{:%Y/%m/%d - %H:%M:%S}", t);
}

void adl_serializer<Timestamp>::from_json(const json &j, Timestamp &t)
{
    t = Timestamp(std::chrono::milliseconds(j.get<int64_t>()));
}

void adl_serializer<User>::to_json(json &j, User &u)
{
    j["uuid"]       = u.uuid;
    j["name"]       = u.name;
    j["created_at"] = u.createdAt;
    j["updated_at"] = u.updatedAt;
}


void adl_serializer<User>::from_json(const json &j, User &u)
{
    try {
        u.uuid      = j.at("uuid").get<std::string>();
        u.name      = j.at("name").get<std::string>();
        u.createdAt = j.at("created_at").get<Timestamp>();
        u.updatedAt = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}


void adl_serializer<Message>::to_json(json &j, Message &m)
{
    j["uuid"]        = m.uuid;
    j["receiver_id"] = m.recieverId;
    j["sender_id"]   = m.senderId;
    j["content"]     = m.content;
    j["created_at"]  = m.createdAt;
    j["updated_at"]  = m.updatedAt;
}


void adl_serializer<Message>::from_json(const json &j, Message &m)
{
    try {
        m.uuid       = j.at("uuid").get<std::string>();
        m.recieverId = j.at("receiver_id").get<std::string>();
        m.senderId   = j.at("sender_id").get<std::string>();
        m.content    = j.at("content").get<std::string>();
        m.createdAt  = j.at("created_at").get<Timestamp>();
        m.updatedAt  = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Request>::to_json(json &j, const Request &req)
{
    j["method"] = req.method;
    j["path"]   = req.path;
    j["body"]   = req.body;
}


void adl_serializer<Request>::from_json(const json &j, Request &req)
{
    try {
        req.method = j.at("method").get<network::Method>();
        req.path   = j.at("path").get<std::string>();
        req.body   = j.at("body").get<json>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Response>::to_json(json &j, const Response &rep)
{
    j["status_code"]    = rep.statusCode;
    j["status_message"] = rep.statusMessage;
    j["body"]           = rep.body;
}

void adl_serializer<Response>::from_json(const json &j, Response &rep)
{
    try {
        rep.statusCode    = j.at("status_code").get<int>();
        rep.statusMessage = j.at("status_message").get<std::string>();
        rep.body          = j.at("body").get<json>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Team>::to_json(json &j, Team &t)
{
    j["uuid"]        = t.uuid;
    j["name"]        = t.name;
    j["description"] = t.description;
    j["user_id"]     = t.userId;
    j["created_at"]  = t.createdAt;
    j["updated_at"]  = t.updatedAt;
}

void adl_serializer<Team>::from_json(const json &j, Team &t)
{
    try {
        t.uuid        = j.at("uuid").get<std::string>();
        t.name        = j.at("name").get<std::string>();
        t.description = j.at("description").get<std::string>();
        t.userId      = j.at("user_id").get<std::string>();
        t.createdAt   = j.at("created_at").get<Timestamp>();
        t.updatedAt   = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Channel>::to_json(json &j, Channel &c)
{
    j["uuid"]        = c.uuid;
    j["name"]        = c.name;
    j["description"] = c.description;
    j["team_id"]     = c.teamId;
    j["user_id"]     = c.userId;
    j["created_at"]  = c.createdAt;
    j["updated_at"]  = c.updatedAt;
}

void adl_serializer<Channel>::from_json(const json &j, Channel &c)
{
    try {
        c.uuid        = j.at("uuid").get<std::string>();
        c.name        = j.at("name").get<std::string>();
        c.description = j.at("description").get<std::string>();
        c.teamId      = j.at("team_id").get<std::string>();
        c.userId      = j.at("user_id").get<std::string>();
        c.createdAt   = j.at("created_at").get<Timestamp>();
        c.updatedAt   = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Thread>::to_json(json &j, Thread &t)
{
    j["uuid"]       = t.uuid;
    j["title"]      = t.title;
    j["body"]       = t.body;
    j["channel_id"] = t.channelId;
    j["user_id"]    = t.userId;
    j["created_at"] = t.createdAt;
    j["updated_at"] = t.updatedAt;
}

void adl_serializer<Thread>::from_json(const json &j, Thread &t)
{
    try {
        t.uuid      = j.at("uuid").get<std::string>();
        t.title     = j.at("title").get<std::string>();
        t.body      = j.at("body").get<std::string>();
        t.channelId = j.at("channel_id").get<std::string>();
        t.userId    = j.at("user_id").get<std::string>();
        t.createdAt = j.at("created_at").get<Timestamp>();
        t.updatedAt = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Subscription>::to_json(json &j, Subscription &s)
{
    j["uuid"]       = s.uuid;
    j["team_id"]    = s.teamId;
    j["user_id"]    = s.userId;
    j["created_at"] = s.createdAt;
    j["updated_at"] = s.updatedAt;
}

void adl_serializer<Subscription>::from_json(const json &j, Subscription &s)
{
    try {
        s.uuid      = j.at("uuid").get<std::string>();
        s.teamId    = j.at("team_id").get<std::string>();
        s.userId    = j.at("user_id").get<std::string>();
        s.createdAt = j.at("created_at").get<Timestamp>();
        s.updatedAt = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Comment>::to_json(json &j, Comment &c)
{
    j["uuid"]       = c.uuid;
    j["message"]    = c.message;
    j["team_id"]    = c.teamId;
    j["user_id"]    = c.userId;
    j["created_at"] = c.createdAt;
    j["updated_at"] = c.updatedAt;
}

void adl_serializer<Comment>::from_json(const json &j, Comment &c)
{
    try {
        c.uuid      = j.at("uuid").get<std::string>();
        c.message   = j.at("message").get<std::string>();
        c.teamId    = j.at("team_id").get<std::string>();
        c.userId    = j.at("user_id").get<std::string>();
        c.createdAt = j.at("created_at").get<Timestamp>();
        c.updatedAt = j.at("updated_at").get<Timestamp>();
    } catch (std::exception &e) {
		throw;
	}
}
}
