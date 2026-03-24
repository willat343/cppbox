#ifndef CPPBOX_IMPL_TIME_KEEPER_HPP
#define CPPBOX_IMPL_TIME_KEEPER_HPP

#include <algorithm>
#include <cmath>
#include <cppbox/exceptions.hpp>
#include <iterator>
#include <limits>
#include <utility>

#include "cppbox/exceptions.hpp"
#include "cppbox/time_keeper.hpp"

namespace cppbox {

template<IsTimePoint Time_>
inline auto TimeKeeperBase<Time_>::interval(const int index) const -> Duration {
    return time(index + 1) - time(index);
}

template<IsTimePoint Time_>
inline auto OrderedTimeKeeper<Time_>::end() const -> Time {
    throw_if(times().empty(), "Failed to compute end: no times exist");
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
    throw_if(!times().empty() && time_ < end(), "Failed to add time: time_ < end().");
    times_.push_back(time_);
}

template<IsTimePoint Time_>
inline void OrderedTimeKeeper<Time_>::reset() {
    times_.clear();
}

template<IsTimePoint Time_>
inline auto OrderedTimeKeeper<Time_>::start() const -> Time {
    return times().front();
}

template<IsTimePoint Time_>
inline int OrderedTimeKeeper<Time_>::size() const {
    return static_cast<int>(times().size());
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
inline auto UniformTimeKeeper<Time_>::end() const -> Time {
    return Time::max();
}

template<IsTimePoint Time_>
inline int UniformTimeKeeper<Time_>::find_index(const Time time_) const {
    // Because integer division ignores the fractional part, we must conditionally subtract one for negative durations.
    return (time_ - start()) / interval() - (time_ < start() ? 1 : 0);
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
inline void UniformTimeKeeper<Time_>::reset() {}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::start() const -> Time {
    return start_;
}

template<IsTimePoint Time_>
inline int UniformTimeKeeper<Time_>::size() const {
    return std::numeric_limits<int>::max();
}

template<IsTimePoint Time_>
inline auto UniformTimeKeeper<Time_>::time(const int index) const -> Time {
    return start() + index * interval();
}

}

#endif
