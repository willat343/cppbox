#ifndef CPPBOX_TRACKING_EVENTS_HPP
#define CPPBOX_TRACKING_EVENTS_HPP

#include <cstddef>
#include <vector>

#include "cppbox/time.hpp"

namespace cppbox {

/**
 * @brief Track event times in monotonic order and query nearby events efficiently.
 *
 * Events are registered in non-decreasing time order. The class stores the timestamps and supports efficient lookups
 * for the latest event at or before a query time and the earliest event at or after a query time.
 *
 * @tparam Time_
 */
template<IsTimePoint Time_>
class TrackingEvents {
public:
    using Time = Time_;
    using Duration = Time::duration;

    /**
     * @brief Initialise an empty event tracker.
     *
     */
    explicit TrackingEvents() = default;

    /**
     * @brief Initialise with the first event.
     *
     * @param time
     */
    explicit TrackingEvents(const Time time);

    /**
     * @brief Check if any events have been registered.
     *
     * @return true if empty
     * @return false otherwise
     */
    bool empty() const;

    /**
     * @brief Check if any events have been registered before `time`.
     *
     * @param time
     * @return true
     * @return false
     */
    bool empty_before(const Time time) const;

    /**
     * @brief Check if any events have been registered after `time`.
     *
     * @param time
     * @return true
     * @return false
     */
    bool empty_after(const Time time) const;

    /**
     * @brief Number of registered events.
     *
     * @return std::size_t
     */
    std::size_t size() const;

    /**
     * @brief Get the first registered event time.
     *
     * @return Time
     */
    Time first_time() const;

    /**
     * @brief Get the last registered event time.
     *
     * @return Time
     */
    Time last_time() const;

    /**
     * @brief Register a new event at a nondecreasing timestamp.
     *
     * @param time
     */
    void register_event(const Time time);

    /**
     * @brief Get the latest event time at or before a query time.
     *
     * Uses binary search with quick checks for first/last time extremes.
     * Complexity: O(1) if query is before first event or after last event, O(log n) otherwise.
     *
     * @param time query time
     * @return Time
     */
    Time previous_time(const Time time) const;

    /**
     * @brief Get the latest event time at or before a query time, searching linearly from the end.
     *
     * Use this when you know the query time is near the end of the event stream.
     * Complexity: O(n) worst case, but O(1) amortized for queries near the end.
     *
     * @param time query time
     * @return Time
     */
    Time previous_time_from_end(const Time time) const;

    /**
     * @brief Get the latest event time at or before a query time, searching linearly from the start.
     *
     * Use this when you know the query time is near the start of the event stream.
     * Complexity: O(n) worst case, but O(1) amortized for queries near the start.
     *
     * @param time query time
     * @return Time
     */
    Time previous_time_from_start(const Time time) const;

    /**
     * @brief Get the earliest event time at or after a query time.
     *
     * Uses binary search with quick checks for first/last time extremes.
     * Complexity: O(1) if query is before first event or after last event, O(log n) otherwise.
     *
     * @param time query time
     * @return Time
     */
    Time next_time(const Time time) const;

    /**
     * @brief Get the earliest event time at or after a query time, searching linearly from the start.
     *
     * Use this when you know the query time is near the start of the event stream.
     * Complexity: O(n) worst case, but O(1) amortized for queries near the start.
     *
     * @param time query time
     * @return Time
     */
    Time next_time_from_start(const Time time) const;

    /**
     * @brief Get the earliest event time at or after a query time, searching linearly from the end.
     *
     * Use this when you know the query time is near the end of the event stream.
     * Complexity: O(n) worst case, but O(1) amortized for queries near the end.
     *
     * @param time query time
     * @return Time
     */
    Time next_time_from_end(const Time time) const;

    /**
     * @brief Get the duration to the previous time.
     *
     * @param time
     * @return Duration
     */
    Duration duration_since(const Time time) const;

    /**
     * @brief Get the duration to the previous time, searching from the end.
     *
     * Use this when you know the query time is near the end of the event stream.
     *
     * @param time
     * @return Duration
     */
    Duration duration_since_from_end(const Time time) const;

    /**
     * @brief Get the duration to the previous time, searching from the start.
     *
     * Use this when you know the query time is near the start of the event stream.
     *
     * @param time
     * @return Duration
     */
    Duration duration_since_from_start(const Time time) const;

    /**
     * @brief Get the duration to the next time.
     *
     * @param time
     * @return Duration
     */
    Duration duration_until(const Time time) const;

    /**
     * @brief Get the duration to the next time, searching from the end.
     *
     * Use this when you know the query time is near the end of the event stream.
     *
     * @param time
     * @return Duration
     */
    Duration duration_until_from_end(const Time time) const;

    /**
     * @brief Get the duration to the next time, searching from the start.
     *
     * Use this when you know the query time is near the start of the event stream.
     *
     * @param time
     * @return Duration
     */
    Duration duration_until_from_start(const Time time) const;

private:
    std::vector<Time> times_;
};

}

#include "cppbox/impl/tracking_events.hpp"

#endif
