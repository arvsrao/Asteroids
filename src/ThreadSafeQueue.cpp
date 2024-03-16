#include <algorithm>
#include "ThreadSafeQueue.h"

/** Filter-in PhaserBlasts according satisfying the predicate.
 *
 * @param predicate the filtering predicate.
 * @return true only if a PhaserBlast was removed.
 * */
template<typename T>
bool ThreadSafeQueue<T>::filter(const std::function<bool(T &)> &predicate) {
    std::lock_guard<std::mutex> lock(_mutex);
    size_t N = _queue.size();
    _queue.erase(std::remove_if(_queue.begin(), _queue.end(), predicate), _queue.end());

    return N > _queue.size();
}

template<typename T>
void ThreadSafeQueue<T>::foreach(const std::function<void(T &)> &func) {
    std::lock_guard<std::mutex> lock(_mutex);
    std::for_each(
            _queue.begin(),
            _queue.end(),
            [&](T &t) { func(t); }
    );
}

template<typename T>
void ThreadSafeQueue<T>::push(T&& t) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.emplace_back(std::move(t));
}

template<typename T>
int ThreadSafeQueue<T>::size() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.size();
}

template<typename T>
void ThreadSafeQueue<T>::pop() {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.pop_front();
}

template<typename T>
const T& ThreadSafeQueue<T>::back() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.back();
}
