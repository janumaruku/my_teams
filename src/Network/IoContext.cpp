/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

#include <algorithm>
#include <system_error>

namespace network {
void IOContext::registerFileDescriptor(const int &fileDescriptor)
{
    _pollFds.push_back({
        .fd = fileDescriptor,
        .events = POLLIN,
        .revents = 0,
    });
}

void IOContext::registerNotifier(const int &fileDescriptor,
    const OnFileDescriptorReady &notifier)
{
    const auto itt = std::ranges::find_if(_pollFds,
        [fileDescriptor](const pollfd item) {
            return item.fd == fileDescriptor;
        });
    if (itt != _pollFds.end())
        return;

    _pollFds.push_back({
        .fd = fileDescriptor,
        .events = POLLIN,
        .revents = 0,
    });
    _notifiers[fileDescriptor] = notifier;
}

void IOContext::postRead(const int &fileDescriptor,
    const OnFileDescriptorReady &handler)
{
    _pendingOperations[fileDescriptor].emplace(OpType::READ, handler);
    updateEventType(fileDescriptor);
}

void IOContext::postWrite(const int &fileDescriptor,
    const OnFileDescriptorReady &handler)
{
    _pendingOperations[fileDescriptor].emplace(OpType::WRITE, handler);
    updateEventType(fileDescriptor);
}

void IOContext::updateEventType(const int &fileDescriptor)
{
    if (_pendingOperations.contains(fileDescriptor) &&
        !_pendingOperations.at(fileDescriptor).empty()) {
        const OpType opType = _pendingOperations.at(fileDescriptor).front().
            first;
        _pollFds.at(fileDescriptor).events = opType == OpType::READ
            ? POLLIN
            : POLLOUT;
    }
}

void IOContext::run()
{
    while (true) {
        if (poll(_pollFds.data(), _pollFds.size(), 10) == -1)
            throw std::system_error(std::make_error_code(std::errc::timed_out));

        std::size_t itt = 0;
        while (itt < _pollFds.size()) {
            if (_pollFds[itt].revents & POLLIN) {
                _notifiers[_pollFds[itt].fd]();
            }

            ++itt;
        }
    }
}

void IOContext::unregisterNotifier(const int &socketFd)
{
    const auto pollFd = std::ranges::find_if(_pollFds,
        [&socketFd](const pollfd &fd) {
            return fd.fd == socketFd;
        });

    if (pollFd != _pollFds.end())
        _pollFds.erase(pollFd);

    const auto notifier = _notifiers.find(socketFd);
    if (notifier != _notifiers.end()) {
        _notifiers.erase(notifier);
    }
}
} // ftp
