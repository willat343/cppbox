#ifndef CPPBOX_TRACKING_DEQUE_HPP
#define CPPBOX_TRACKING_DEQUE_HPP

#include <deque>
#include <unordered_map>
#include <unordered_set>

namespace cppbox {

/**
 * @brief A container with the behaviour of `std::deque<T>` but with additional tracking of unique elements.
 *
 * An example usage of this class is as a schedule, when the user requires knowledge about the number or existence of
 * specific elements in the schedule.
 *
 * @tparam T
 */
template<typename T>
class TrackingDeque {
public:
    /** Deque functionality */

    using value_type = std::deque<T>::value_type;
    using allocator_type = std::deque<T>::allocator_type;
    using size_type = std::deque<T>::size_type;
    using difference_type = std::deque<T>::difference_type;
    using reference = std::deque<T>::reference;
    using const_reference = std::deque<T>::const_reference;
    using pointer = std::deque<T>::pointer;
    using const_pointer = std::deque<T>::const_pointer;
    using iterator = std::deque<T>::iterator;
    using const_iterator = std::deque<T>::const_iterator;
    using reverse_iterator = std::deque<T>::reverse_iterator;
    using const_reverse_iterator = std::deque<T>::const_reverse_iterator;

    iterator begin();

    const_iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;

    reverse_iterator rbegin();

    const_reverse_iterator rbegin() const;

    const_reverse_iterator crbegin() const;

    reverse_iterator rend();

    const_reverse_iterator rend() const;

    const_reverse_iterator crend() const;

    reference at(size_type pos);

    const_reference at(size_type pos) const;

    reference operator[](size_type pos);

    const_reference operator[](size_type pos) const;

    reference front();

    const_reference front() const;

    reference back();

    const_reference back() const;

    bool empty() const;

    size_type size() const;

    void clear();

    template<class... Args>
    void emplace_back(Args&&... args);

    iterator erase(iterator pos);

    iterator erase(const_iterator pos);

    void push_front(const_reference element);

    void push_back(const_reference element);

    void pop_front();

    void pop_back();

    /** Tracking functionality */

    /**
     * @brief Get the number of `element` objects.
     *
     * @param element
     * @return size_type
     */
    size_type count(const_reference element) const;

    /**
     * @brief Get the number of tracked `element` objects.
     *
     * @return size_type
     */
    size_type count_tracked() const;

    /**
     * @brief Has at least one object of each tracked element.
     *
     * @return true
     * @return false
     */
    bool has_all_tracked() const;

    /**
     * @brief Has any object from any tracked element.
     *
     * @return true
     * @return false
     */
    bool has_any_tracked() const;

    /**
     * @brief Add `element` as an object to track. Does nothing if `element` is already tracked.
     *
     * @param element
     */
    void track(const_reference element);

    /**
     * @brief Remove `element` as an object to track. Does nothing if `element is not tracked.
     *
     * @param element
     */
    void untrack(const_reference element);

private:
    /**
     * @brief Decrements the counter for `element` and if zero removes it entirely.
     *
     * @param element
     */
    void decrement_counter(const_reference element);

    // Deque container
    std::deque<T> deque_;

    // Count of elements
    std::unordered_map<T, size_type> counter_;

    // Tracked elements
    std::unordered_set<T> tracked_;
};

}

#include "cppbox/impl/tracking_deque.hpp"

#endif
