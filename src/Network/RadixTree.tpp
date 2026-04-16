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
void Router<TClientState>::RadixTree::Node::add(
    const std::vector<std::string> &words, const Method &method,
    const std::vector<Handler> middles,
    std::initializer_list<Handler> handles)
{
    Node *tempNode = this;
    for (std::size_t count = 1; count < words.size(); ++count) {
        const auto &word = words[count];
        if (word[0] == ':' && !tempNode->param.empty() && tempNode->param != word) {
            std::cerr << utils::RED << "Param already defined in this path: " <<
                word << " | " << tempNode->param <<
                utils::RESET << std::endl;
            return;
        }
        if (word[0] == ':') {
            if (tempNode->paramNode == nullptr) {
                tempNode->param     = word;
                tempNode->paramNode = std::make_unique<Node>(word);
            }
            tempNode = tempNode->paramNode.get();
            continue;
        }
        if (!tempNode->children.contains(word))
            tempNode->children[word] = std::make_unique<Node>(word);
        tempNode = tempNode->children[word].get();
    }
    const auto foundMethod = std::ranges::find(tempNode->methods, method);
    if (tempNode->isPath && foundMethod != tempNode->methods.end()) {
        std::cerr << utils::YELLOW << "Path " << std::quoted(
                "/" + utils::StringUtils::toString(words, '/')) <<
            " already registered" << utils::RESET
            << std::endl;
        return;
    }
    tempNode->middlewares.insert(tempNode->middlewares.end(),
        middles.begin(), middles.end());
    if (handles.size() > 0) {
        tempNode->middlewares.insert(tempNode->middlewares.end(), handles.begin(),
            handles.begin() + handles.size() - 1);
        tempNode->handler = *(handles.begin() + handles.size() - 1);
    }
    tempNode->isPath  = true;
    tempNode->methods.emplace_back(method);
}

template <typename TClientState>
void Router<TClientState>::RadixTree::Node::print(
    const Node *node) noexcept
{
    printHelper(node, "");
}

template <typename TClientState>
void Router<TClientState>::RadixTree::Node::printHelper(
    const Node *node, const std::string &path) noexcept
{
    std::string currentPath = path.empty() ? "/" + node->word : path + "/" + node->word;
    
    // Handle root node case (when word is empty from split)
    if (node->word.empty())
        currentPath = path;
    
    if (node->isPath) {
        std::cout << currentPath << std::endl;
    }

    if (node->paramNode)
        printHelper(node->paramNode.get(), currentPath);

    for (const auto &[key, value]: node->children)
        printHelper(value.get(), currentPath);
}

template <typename TClientState>
void Router<TClientState>::RadixTree::add(const std::vector<std::string> &words,
    const Method &method, std::initializer_list<Handler> handlers)
{
    if (words.empty())
        return;

    if (!_root.contains(words[0]))
        _root[words[0]] = std::make_unique<Node>(words[0]);
    Node *tempNode = _root.at(words[0]).get();

    tempNode->add(words, method, {}, handlers);
}

template <typename TClientState>
StatusCode Router<TClientState>::RadixTree::handle(Context &context)
{
    auto path = context.path();
    Node *node;
    std::vector<Handler> middlewares;
    std::vector<std::pair<std::string, std::string>> params;
    if (path.empty() || path[0] != '/') {
        node = nullptr;
    } else {
        node = find(utils::StringUtils::split(&path[1], '/'), middlewares,
            params);
    }

    if (node == nullptr || !node->isPath)
        return StatusCode::NOT_FOUND;
    if (std::ranges::find(node->methods, context.getRequest().method) == node->
        methods.end())
        return StatusCode::METHOD_NOT_ALLOWED;

    context.addMiddlewares(middlewares);
    context.setHandler(node->handler);
    context.addParams(params);

    return StatusCode::STATUS_OK;
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

    return res;
}

// template <typename TClientState>
// void Router<TClientState>::RadixTree::getPaths(std::vector<std::string> &get,
//     std::vector<std::string> &post, std::vector<std::string> &put,
//     std::vector<std::string> &del)
// {
//
// }

template <typename TClientState>
void Router<TClientState>::RadixTree::printPaths() const noexcept
{
    for (const auto &node: std::ranges::views::values(_root)) {
        Node::print(node.get());
    }
}

template <typename TClientState>
Router<TClientState>::RadixTree::Node *Router<TClientState>::RadixTree
::find(const std::vector<std::string> &words, std::vector<Handler> &middlewares,
    std::vector<std::pair<std::string, std::string>> &params)
{
    const auto itt = std::ranges::find_if(_root, [words](const auto &elem) {
        return words[0] == elem.first;
    });
    if (itt == _root.end()) {
        return nullptr;
    }

    Node *res = itt->second.get();
    middlewares.insert(middlewares.end(), res->middlewares.begin(),
        res->middlewares.end());
    for (std::size_t count = 1; count < words.size(); ++count) {
        if (res->children.contains(words[count])) {
            res = res->children.at(words[count]).get();
            middlewares.insert(middlewares.end(), res->middlewares.begin(),
                res->middlewares.end());
        } else if (res->paramNode) {
            params.emplace_back(res->param, words[count]);
            res = res->paramNode.get();
            middlewares.insert(middlewares.end(), res->middlewares.begin(),
                res->middlewares.end());
        } else {
            middlewares.clear();
            return nullptr;
        }
    }

    return res;
}
}
