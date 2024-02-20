#include "MessageQueue.h"
#include <thread>

/** Implementation of class MessageQueue */
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using move semantics.
    // The received object should then be returned by the receive function.
    std::unique_lock<std::mutex> uLock(_mutex);
    _condition.wait(uLock, [this] { return !_queue.empty(); });
    T v = std::move(_queue.front());
    _queue.pop_front(); // consider _queue.clear();
    return v;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // The method send should use the mechanisms std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> uLock(_mutex);
    _queue.emplace_back(msg);
    _condition.notify_one();
}