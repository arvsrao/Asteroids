#include <algorithm>

#include "ThreadSafeQueue.h"

/** Filter-in elements of the collection of T satisfying the predicate.
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

/** Apply a side effect to each T in the collection.
 *
 * @param func side effect being applied.
 * */
template<typename T>
void ThreadSafeQueue<T>::foreach(const std::function<void(T &)> &func) {
    std::lock_guard<std::mutex> lock(_mutex);
    std::for_each(
            _queue.begin(),
            _queue.end(),
            [&](T &t) { func(t); }
    );
}

/** Add a new T to the collection.
 *
 * @param t the new member being added.
 * */
template<typename T>
void ThreadSafeQueue<T>::push(T&& t) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.emplace_back(std::move(t));
}

/** The size of the underlying collection */
template<typename T>
int ThreadSafeQueue<T>::size() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.size();
}

/** Remove the element at the front of the queue. */
template<typename T>
void ThreadSafeQueue<T>::pop() {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.pop_front();
}

/** Get reference to the last element of the queue. */
template<typename T>
const T& ThreadSafeQueue<T>::back() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.back();
}
