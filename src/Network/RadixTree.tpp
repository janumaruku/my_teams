/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** RadixTree
*/

#pragma once

#include "constants.hpp"
#include "StringUtils.hpp"

namespace network {
template <typename TClientState>
Router<TClientState>::RadixTree::Node::Node(): word{"/"}, parent{nullptr}
{}

template <typename TClientState>
Router<TClientState>::RadixTree::Node::Node(const std::string &nodeWord,
    Node *nodeParent): word{nodeWord}, parent{nodeParent}
{}

template <typename TClientState>
void Router<TClientState>::RadixTree::add(const std::vector<std::string> &words,
    std::initializer_list<Handler> handlers)
{
    if (words.empty())
        return;

    if (!_root.contains(words[0]))
        _root[words[0]] = std::make_unique<Node>(words[0]);
    Node *tempNode = _root.at(words[0]).get();

    for (std::size_t count = 1; count < words.size(); ++count) {
        const auto &word = words[count];
        if (word[0] == ':' && !tempNode->param.empty()) {
            std::cerr << utils::RED << "Param already defined in this path" <<
                utils::RESET << std::endl;
        } else if (tempNode->param.empty()) {
            tempNode->param     = word;
            tempNode->paramNode = std::make_unique<Node>(word);
            tempNode            = tempNode->paramNode.get();
            continue;
        }
        if (!tempNode->children.contains(word))
            tempNode->children[word] = std::make_unique<Node>(word);
        tempNode = tempNode->children[word].get();
    }
    tempNode->handlers.insert(tempNode->handlers.end(), handlers.begin(),
        handlers.end());
    tempNode->isPath = true;
}

template <typename TClientState>
void Router<TClientState>::RadixTree::handle(Context &context)
{
    auto path = context.path();
    Node *node;
    if (path.empty() || path[0] != '/') {
        node = nullptr;
    } else {
        node = find(utils::StringUtils::split(&path[1], '/'));
    }

    if (node == nullptr || !node->isPath) {
        context.abortWithStatus(StatusCode::NOT_FOUND);
    } else {
        for (auto &handler: node->handlers) {
            handler(&context);
        }
    }
}

template <typename TClientState>
Router<TClientState>::RadixTree::Node *Router<TClientState>::RadixTree
::find(const std::vector<std::string> &words)
{
    const auto itt = std::ranges::find_if(_root, [words](const auto &elem) {
       return words[0] == elem.first;
    });
    if (itt == _root.end()) {
        return nullptr;
    }

    Node *res = itt->second.get();
    for (std::size_t count = 1; count < words.size(); ++count) {
        if (res->children.contains(words[count]))
            res = res->children.at(words[count]).get();
        else if (res->paramNode)
            res = res->paramNode.get();
        else
            return nullptr;
    }

    return  res;
}
}
