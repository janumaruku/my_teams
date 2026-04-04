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
void IOContext::registerNotifier(const int &fileDescriptor,
    const OnFileDescriptorReady &notifier)
{
    _pollFds.push_back({
        .fd = fileDescriptor,
        .events = POLLIN,
        .revents = 0,
    });
    _notifiers[fileDescriptor] = notifier;
}

void IOContext::registerFileDescriptor(const int &fileDescriptor)
{
    _pollFds.push_back({
        .fd = fileDescriptor,
        .events = POLLIN,
        .revents = 0,
    });
}

void IOContext::postRead(const int &fileDescriptor,
    const OnFileDescriptorReady &handler)
{
    _pendingOperations[fileDescriptor].emplace(OpType::READ, handler);
    updatePollEvent(fileDescriptor);
}

void IOContext::postWrite(const int &fileDescriptor,
    const OnFileDescriptorReady &handler)
{
    _pendingOperations[fileDescriptor].emplace(OpType::WRITE, handler);
    updatePollEvent(fileDescriptor);
}

void IOContext::run()
{
    while (true) {
        if (poll(_pollFds.data(), _pollFds.size(), 10) == -1)
            throw std::system_error(std::make_error_code(std::errc::timed_out));

        std::size_t itt = 0;
        while (itt < _pollFds.size()) {
            int fd = _pollFds[itt].fd;

            if (_pollFds[itt].revents & (POLLIN | POLLOUT)) {
                if (_pendingOperations.contains(fd) &&
                    !_pendingOperations[fd].empty()) {
                    auto [opType, handler] = _pendingOperations[fd].front();
                    _pendingOperations[fd].pop();
                    handler();
                    updatePollEvent(fd);
                } else
                    _notifiers[fd]();
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

void IOContext::updatePollEvent(const int &fileDescriptor)
{
    const auto itt = std::ranges::find_if(_pollFds,
        [&fileDescriptor](const pollfd &fd) {
            return fd.fd == fileDescriptor;
        });

    if (itt == _pollFds.end())
        return;

    if (_pendingOperations.contains(itt->fd) && !_pendingOperations[itt->fd].
        empty()) {
        const auto opType = _pendingOperations[itt->fd].front().first;
        itt->events = opType == OpType::READ ? POLLIN : POLLOUT;
        return;
    }

    itt->events = POLLIN;
}
} // ftp
