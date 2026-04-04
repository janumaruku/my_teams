/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#ifndef MYFTP_IOCONTEXT_HPP
#define MYFTP_IOCONTEXT_HPP

#include <functional>
#include <poll.h>
#include <queue>
#include <unordered_map>
#include <vector>

namespace network {
class IOContext {
public:
    enum class OpType {
        READ,
        WRITE
    };

    using OnFileDescriptorReady = std::function<void()>;

    using PendingOperation = std::pair<OpType, OnFileDescriptorReady>;

    IOContext() = default;

    void registerNotifier(const int &fileDescriptor,
        const OnFileDescriptorReady &notifier);

    void registerFileDescriptor(const int &fileDescriptor);

    void postRead(const int &fileDescriptor,
        const OnFileDescriptorReady &handler);

    void postWrite(const int &fileDescriptor,
        const OnFileDescriptorReady &handler);

    void run();

    void unregisterNotifier(const int &socketFd);

private:
    std::vector<pollfd> _pollFds;
    std::unordered_map<int, OnFileDescriptorReady> _notifiers;
    std::unordered_map<int, std::queue<PendingOperation> > _pendingOperations;

    void updatePollEvent(const int &fileDescriptor);
};
} // ftp

#endif //MYFTP_IOCONTEXT_HPP
