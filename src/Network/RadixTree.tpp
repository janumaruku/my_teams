/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** RadixTree
*/

#pragma once

#include "constants.hpp"

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
    Handler handler)
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
    tempNode->handler = std::move(handler);
}
}