#ifndef CPPBOX_IMPL_TRACKING_EVENTS_HPP
#define CPPBOX_IMPL_TRACKING_EVENTS_HPP

#include <algorithm>
#include <iterator>

#include "cppbox/exceptions.hpp"
#include "cppbox/tracking_events.hpp"

namespace cppbox {

template<IsTimePoint Time_>
inline TrackingEvents<Time_>::TrackingEvents(const Time time) {
    register_event(time);
}

template<IsTimePoint Time_>
inline bool TrackingEvents<Time_>::empty() const {
    return times_.empty();
}

template<IsTimePoint Time_>
inline bool TrackingEvents<Time_>::empty_before(const Time time) const {
    return times_.empty() || time < first_time();
}

template<IsTimePoint Time_>
inline bool TrackingEvents<Time_>::empty_after(const Time time) const {
    return times_.empty() || time > last_time();
}

template<IsTimePoint Time_>
inline std::size_t TrackingEvents<Time_>::size() const {
    return times_.size();
}

template<IsTimePoint Time_>
inline auto TrackingEvents<Time_>::first_time() const -> Time {
    throw_if(empty(), "No events available.");
    return times_.front();
}

template<IsTimePoint Time_>
inline auto TrackingEvents<Time_>::last_time() const -> Time {
    throw_if(empty(), "No events available.");
    return times_.back();
}

template<IsTimePoint Time_>
inline void TrackingEvents<Time_>::register_event(const Time time) {
    if (!times_.empty()) {
        throw_if(time < times_.back(), "Event time (" + cppbox::to_string(time) + ") precedes last event time (" +
                                               cppbox::to_string(times_.back()) + ").");
    }
    times_.push_back(time);
}

template<IsTimePoint Time_>
inline auto TrackingEvents<Time_>::previous_time(const Time time) const -> Time {
    throw_if(empty(), "No events available.");
    const auto it = std::upper_bound(times_.cbegin(), times_.cend(), time);
    throw_if(it == times_.cbegin(), "No event available at or before query time " + cppbox::to_string(time) + ".");
    return *std::prev(it);
}

template<IsTimePoint Time_>
inline auto TrackingEvents<Time_>::next_time(const Time time) const -> Time {
    throw_if(empty(), "No events available.");
    const auto it = std::lower_bound(times_.cbegin(), times_.cend(), time);
    throw_if(it == times_.cend(), "No event available at or after query time " + cppbox::to_string(time) + ".");
    return *it;
}

template<IsTimePoint Time_>
inline auto TrackingEvents<Time_>::duration_since(const Time time) const -> Duration {
    return time - previous_time(time);
}

template<IsTimePoint Time_>
inline auto TrackingEvents<Time_>::duration_until(const Time time) const -> Duration {
    return next_time(time) - time;
}

}

#endif
