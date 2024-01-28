#ifndef ASTEROIDS_MESSAGEQUEUE_H
#define ASTEROIDS_MESSAGEQUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template <typename T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    std::deque<T> _queue;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif //ASTEROIDS_MESSAGEQUEUE_H
