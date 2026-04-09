#ifndef CPPBOX_IMPL_TIME_KEEPER_HPP
#define CPPBOX_IMPL_TIME_KEEPER_HPP

#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>
#include <string>
#include <utility>

#include "cppbox/exceptions.hpp"
#include "cppbox/time_keeper.hpp"

namespace cppbox {

template<IsTimePoint Time_>
inline bool TimeKeeperBase<Time_>::empty() const {
    return size() == 0;
}

template<IsTimePoint Time_>
inline bool TimeKeeperBase<Time_>::has_time(const Time time_) const {
    return time(find_index(time_)) == time_;
}

template<IsTimePoint Time_>
inline bool TimeKeeperBase<Time_>::has_time_within(const Time time_) const {
    const int index = find_index(time_);
    return time(index) == time_ || index + 1 < size();
}

template<IsTimePoint Time_>
inline auto TimeKeeperBase<Time_>::interval(const int index) const -> Duration {
    return time(index + 1) - time(index);
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::change_end_time(const Time time_) {
    throw_if(this->empty(), "End time cannot be changed as there are no times.");
    throw_if(size() >= 2 && time_ < time(size() - 2),
            "Attempted to change end time " + cppbox::to_string(end()) + " to " + cppbox::to_string(time_) +
                    " which would violate monotonic time ordering. Previous time is " +
                    cppbox::to_string(time(size() - 2)) + ".");
    times_[size() - 1] = time_;
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::change_start_time(const Time time_) {
    throw_if(this->empty(), "Start time cannot be changed as there are no times.");
    throw_if(size() >= 2 && time_ > time(1),
            "Attempted to change start time " + cppbox::to_string(start()) + " to " + cppbox::to_string(time_) +
                    " which would violate monotonic time ordering. Next time is " + cppbox::to_string(time(1)) + ".");
    times_[0] = time_;
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::change_time(const int index, const Time time_) {
    throw_if(index < 0 || index > size(),
            "Index " + std::to_string(index) + " out of bounds [0, " + std::to_string(size()) + ").");
    throw_if((index != 0 && time_ < time(index - 1)) || (index + 1 != size() && time_ > time(index + 1)),
            "Attempted to change time " + cppbox::to_string(time(index)) + " at index " + std::to_string(index) +
                    " to " + cppbox::to_string(time_) +
                    " which would violate monotonic time ordering. Bounds from adjacent times is " +
                    (index == 0 ? "(-inf" : "[" + cppbox::to_string(time(index - 1))) + ", " +
                    (index + 1 == size() ? "+inf)" : cppbox::to_string(time(index + 1)) + "]") + ".");
    times_[index] = time_;
}

template<IsTimePoint Time_>
inline auto OrderedTimeKeeper<Time_>::end() const -> Time {
    throw_if(this->empty(), "Failed to compute end: no times exist");
    return times().back();
}

template<IsTimePoint Time_>
inline int OrderedTimeKeeper<Time_>::find_index(const Time time_) const {
    // std::lower_bound is logarithmic complexity, returning the first iterator that breaks the comparison.
    const auto lower = std::lower_bound(times().cbegin(), times().cend(), time_, std::less_equal<Time>());
    // std::distance is constant complexity for LegacyRandomAccessIterator.
    return std::distance(times().cbegin(), lower) - 1;
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::push_back(const Time time_) {
    throw_if(!this->empty() && time_ < end(), "Failed to add time: time_ < end().");
    times_.push_back(time_);
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::require_time(const Time time_) {
    if (!has_time(time_)) {
        throw_if(time_ < end(), "Required time " + cppbox::to_string(time_) +
                                        " could not be added because it precedes end() == " + cppbox::to_string(end()) +
                                        ".");
        push_back(time_);
    }
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::require_time_within(const Time time_) {
    if (!has_time_within(time_)) {
        throw_if(time_ < end(), "Required time " + cppbox::to_string(time_) +
                                        " could not be added because it precedes end() == " + cppbox::to_string(end()) +
                                        ".");
        push_back(time_);
    }
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::reset() {
    times_.clear();
}

template<IsTimePoint Time_>
inline int OrderedTimeKeeper<Time_>::size() const {
    return static_cast<int>(times().size());
}

template<IsTimePoint Time_>
inline auto OrderedTimeKeeper<Time_>::start() const -> Time {
    return times().front();
}

template<IsTimePoint Time_>
inline auto OrderedTimeKeeper<Time_>::times() const -> const std::vector<Time>& {
    return times_;
}

template<IsTimePoint Time_>
inline auto OrderedTimeKeeper<Time_>::time(const int index) const -> Time {
    return times().at(index);
}

template<IsTimePoint Time_>
inline UniformTimeKeeper<Time_>::UniformTimeKeeper() : UniformTimeKeeper(to_time<Time>(0), to_duration<Duration>(1)) {}

template<IsTimePoint Time_>
inline UniformTimeKeeper<Time_>::UniformTimeKeeper(const Time start_, const Duration interval_)
    : start_(start_), interval_(interval_) {
    throw_if(interval_ == Duration::zero(), "UniformTimeKeeper interval cannot be zero.");
}

template<IsTimePoint Time_>
inline void UniformTimeKeeper<Time_>::change_start_time(const Time time_) {
    start_ = time_;
}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::end() const -> Time {
    return Time::max();
}

template<IsTimePoint Time_>
inline int UniformTimeKeeper<Time_>::find_index(const Time time_) const {
    // Because integer division ignores the fractional part, we must conditionally subtract one for negative durations.
    return (time_ - this->start()) / interval() - (time_ < this->start() ? 1 : 0);
}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::interval(const int) const -> Duration {
    return interval();
}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::interval() const -> Duration {
    return interval_;
}

template<IsTimePoint Time_>
inline void UniformTimeKeeper<Time_>::require_time(const Time time_) {
    throw_if(!has_time(time_), "Required time " + cppbox::to_string(time_) + " does not exist.");
}

template<IsTimePoint Time_>
inline void UniformTimeKeeper<Time_>::require_time_within(const Time time_) {
    throw_if(!has_time_within(time_),
            "Required time " + cppbox::to_string(time_) + " does not exist not is between two times.");
}

template<IsTimePoint Time_>
inline void UniformTimeKeeper<Time_>::reset() {}

template<IsTimePoint Time_>
inline int UniformTimeKeeper<Time_>::size() const {
    return std::numeric_limits<int>::max();
}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::start() const -> Time {
    return start_;
}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::time(const int index) const -> Time {
    return this->start() + index * interval();
}

}

#endif
