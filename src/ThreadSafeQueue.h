#ifndef ASTEROIDS_THREADSAFEQUEUE_H
#define ASTEROIDS_THREADSAFEQUEUE_H

#include <mutex>
#include <deque>

template<typename T>
class ThreadSafeQueue {
public:

    void pop();
    int size();

    const T& back();
    void push(T &&t);
    void foreach(const std::function<void(T &)> &func);
    bool filter(const std::function<bool(T&)>& predicate);

private:
    std::mutex _mutex;
    std::deque<T> _queue;
};

#endif //ASTEROIDS_THREADSAFEQUEUE_H
