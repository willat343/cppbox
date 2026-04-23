#ifndef CPPBOX_IMPL_TRACKING_DEQUE_HPP
#define CPPBOX_IMPL_TRACKING_DEQUE_HPP

#include <algorithm>
#include <numeric>

#include "cppbox/tracking_deque.hpp"

namespace cppbox {

template<typename T>
inline auto TrackingDeque<T>::begin() -> iterator {
    return deque_.begin();
}

template<typename T>
inline auto TrackingDeque<T>::begin() const -> const_iterator {
    return deque_.begin();
}

template<typename T>
inline auto TrackingDeque<T>::cbegin() const -> const_iterator {
    return deque_.begin();
}

template<typename T>
inline auto TrackingDeque<T>::end() -> iterator {
    return deque_.end();
}

template<typename T>
inline auto TrackingDeque<T>::end() const -> const_iterator {
    return deque_.end();
}

template<typename T>
inline auto TrackingDeque<T>::cend() const -> const_iterator {
    return deque_.end();
}

template<typename T>
inline auto TrackingDeque<T>::rbegin() -> reverse_iterator {
    return deque_.rbegin();
}

template<typename T>
inline auto TrackingDeque<T>::rbegin() const -> const_reverse_iterator {
    return deque_.rbegin();
}

template<typename T>
inline auto TrackingDeque<T>::crbegin() const -> const_reverse_iterator {
    return deque_.rbegin();
}

template<typename T>
inline auto TrackingDeque<T>::rend() -> reverse_iterator {
    return deque_.rend();
}

template<typename T>
inline auto TrackingDeque<T>::rend() const -> const_reverse_iterator {
    return deque_.rend();
}

template<typename T>
inline auto TrackingDeque<T>::crend() const -> const_reverse_iterator {
    return deque_.rend();
}

template<typename T>
inline auto TrackingDeque<T>::count(const_reference element) const -> size_type {
    return counter_.contains(element) ? counter_.at(element) : 0;
}

template<typename T>
inline auto TrackingDeque<T>::at(size_type pos) -> reference {
    return deque_.at(pos);
}

template<typename T>
inline auto TrackingDeque<T>::at(size_type pos) const -> const_reference {
    return deque_.at(pos);
}

template<typename T>
inline auto TrackingDeque<T>::operator[](size_type pos) -> reference {
    return deque_[pos];
}

template<typename T>
inline auto TrackingDeque<T>::operator[](size_type pos) const -> const_reference {
    return deque_[pos];
}

template<typename T>
inline auto TrackingDeque<T>::front() -> reference {
    return deque_.front();
}

template<typename T>
inline auto TrackingDeque<T>::front() const -> const_reference {
    return deque_.front();
}

template<typename T>
inline auto TrackingDeque<T>::back() -> reference {
    return deque_.back();
}

template<typename T>
inline auto TrackingDeque<T>::back() const -> const_reference {
    return deque_.back();
}

template<typename T>
bool TrackingDeque<T>::empty() const {
    return deque_.empty();
}

template<typename T>
inline auto TrackingDeque<T>::size() const -> size_type {
    return deque_.size();
}

template<typename T>
inline void TrackingDeque<T>::clear() {
    deque_.clear();
    counter_.clear();
}

template<typename T>
template<class... Args>
inline void TrackingDeque<T>::emplace_back(Args&&... args) {
    deque_.emplace_back(std::forward<Args>(args)...);
    ++counter_[deque_.back()];
}

template<typename T>
inline auto TrackingDeque<T>::erase(iterator pos) -> iterator {
    decrement_counter(*pos);
    return deque_.erase(pos);
}

template<typename T>
inline auto TrackingDeque<T>::erase(const_iterator pos) -> iterator {
    decrement_counter(*pos);
    return deque_.erase(pos);
}

template<typename T>
inline void TrackingDeque<T>::push_back(const_reference element) {
    deque_.push_back(element);
    ++counter_[deque_.back()];
}

template<typename T>
inline void TrackingDeque<T>::push_front(const_reference element) {
    deque_.push_front(element);
    ++counter_[deque_.front()];
}

template<typename T>
void TrackingDeque<T>::pop_back() {
    throw_if(empty(), "Failed to pop_back(), schedule is empty.");
    decrement_counter(deque_.back());
    deque_.pop_back();
}

template<typename T>
void TrackingDeque<T>::pop_front() {
    throw_if(empty(), "Failed to pop_front(), schedule is empty.");
    decrement_counter(deque_.front());
    deque_.pop_front();
}

template<typename T>
inline auto TrackingDeque<T>::count_tracked() const -> size_type {
    return std::accumulate(tracked_.cbegin(), tracked_.cend(), 0,
            [this](const_reference element) { return count(element); });
}

template<typename T>
inline bool TrackingDeque<T>::has_all_tracked() const {
    return std::all_of(tracked_.cbegin(), tracked_.cend(),
            [this](const_reference element) { return counter_.contains(element); });
}

template<typename T>
inline bool TrackingDeque<T>::has_any_tracked() const {
    return std::any_of(tracked_.cbegin(), tracked_.cend(),
            [this](const_reference element) { return counter_.contains(element); });
}

template<typename T>
inline void TrackingDeque<T>::track(const_reference element) {
    tracked_.insert(element);
}

template<typename T>
inline void TrackingDeque<T>::untrack(const_reference element) {
    tracked_.erase(element);
}

template<typename T>
inline void TrackingDeque<T>::decrement_counter(const_reference element) {
    --counter_[element];
    if (counter_[element] == 0) {
        counter_.erase(element);
    }
}

}

#endif
