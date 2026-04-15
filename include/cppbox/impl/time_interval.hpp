#ifndef CPPBOX_IMPL_TIME_INTERVAL_HPP
#define CPPBOX_IMPL_TIME_INTERVAL_HPP

#include "cppbox/exceptions.hpp"
#include "cppbox/time_interval.hpp"

namespace cppbox {

template<IsTimePoint Time_>
inline TimeInterval<Time_>::TimeInterval() : TimeInterval(Time(), Time::max()) {}

template<IsTimePoint Time_>
inline TimeInterval<Time_>::TimeInterval(const Time& start_, const Time& end_) : start_(start_), end_(end_) {
    throw_if(start_ > end_, "Time bounds cannot have start time after end time.");
}

template<IsTimePoint Time_>
inline bool TimeInterval<Time_>::contains(const Time time) const {
    return time >= start() && time <= end();
}

template<IsTimePoint Time_>
inline auto TimeInterval<Time_>::end() const -> const Time& {
    return end_;
}

template<IsTimePoint Time_>
inline auto TimeInterval<Time_>::end() -> Time& {
    return const_cast<Time&>(std::as_const(*this).end());
}

template<IsTimePoint Time_>
inline auto TimeInterval<Time_>::span() const -> Duration {
    return end() - start();
}

template<IsTimePoint Time_>
inline auto TimeInterval<Time_>::start() const -> const Time& {
    return start_;
}

template<IsTimePoint Time_>
inline auto TimeInterval<Time_>::start() -> Time& {
    return const_cast<Time&>(std::as_const(*this).start());
}

template<IsTimePoint Time_>
inline std::string TimeInterval<Time_>::to_string() const {
    return "[" + cppbox::to_string(start()) + ", " + cppbox::to_string(end()) + "]";
}

template<IsTimePoint Time_>
std::ostream& operator<<(std::ostream& os, const TimeInterval<Time_>& interval) {
    return os << interval.to_string();
}

template<IsTimePoint Time>
inline TimeInterval<Time> intersection_of(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs) {
    throw_if(!is_overlapping<Time>(lhs, rhs), "Time bounds are not overlapping.");
    return TimeInterval<Time>(std::max(lhs.start(), rhs.start()), std::min(lhs.end(), rhs.end()));
}

template<IsTimePoint Time>
inline bool is_overlapping(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs) {
    return lhs.end() >= rhs.start() || rhs.end() >= lhs.start();
}

template<IsTimePoint Time>
inline TimeInterval<Time> union_of(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs) {
    throw_if(!is_overlapping<Time>(lhs, rhs), "Time bounds are not overlapping.");
    return TimeInterval<Time>(std::min(lhs.start(), rhs.start()), std::max(lhs.end(), rhs.end()));
}

}

#endif
