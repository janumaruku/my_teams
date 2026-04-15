/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MYTEAMS_TYPES_HPP
#define MYTEAMS_TYPES_HPP

#include <chrono>
#include <ctime>
#include <string>

constexpr unsigned int MAX_NAME_LENGTH = 32;
constexpr unsigned int MAX_DESCRIPTION_LENGTH = 255;
constexpr unsigned int MAX_BODY_LENGTH = 512;

using Timestamp = std::chrono::system_clock::time_point; 

using Team = struct Team {
    std::string uuid;
    std::string name;
    std::string description;
    std::string userId;
    Timestamp createdAt;
    Timestamp updatedAt;

};

using Channel = struct Channel {
    std::string uuid;
    std::string name;
    std::string description;
    std::string teamId;
    std::string userId;
    Timestamp createdAt;
    Timestamp updatedAt;
};

using Thread = struct Thread {
    std::string uuid;
    std::string title;
    std::string body;
    std::string channelId;
    std::string userId;
    Timestamp createdAt;
    Timestamp updatedAt;
};

using Subscription = struct Subscription {
    std::string uuid;
    std::string teamId;
    std::string userId;
    Timestamp createdAt;
    Timestamp updatedAt;
};


using Comment = struct Comment {
    std::string uuid;
    std::string message;
    std::string teamId;
    std::string userId;
    Timestamp createdAt;
    Timestamp updatedAt;
};

using User = struct User {
    std::string uuid;
    std::string name;
    Timestamp createdAt;
    Timestamp updatedAt;
};

using Message = struct Message {
    std::string uuid;
    std::string recieverId;
    std::string senderId;
    std::string content;
    Timestamp createdAt;
    Timestamp updatedAt;
};

#endif
