#ifndef CPPBOX_IMPL_TIME_INTERVALS_HPP
#define CPPBOX_IMPL_TIME_INTERVALS_HPP

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>

#include "cppbox/exceptions.hpp"
#include "cppbox/time_intervals.hpp"

namespace cppbox {

template<IsTimePoint Time, ForwardRangeOf<TimeInterval<Time>> Intervals>
inline bool contains(const Intervals& intervals, const Time time) {
    return std::ranges::any_of(intervals,
            [time](const TimeInterval<Time>& interval) { return interval.contains(time); });
}

template<IsTimePoint Time, ForwardRangeOf<TimeInterval<Time>> Intervals>
inline bool contains_sorted_disjoint(const Intervals& intervals, const Time time) {
    // The first interval ending at or after the time contains it if it starts at or before it
    const auto it = std::ranges::lower_bound(intervals, time, std::less<>{},
            [](const TimeInterval<Time>& interval) { return interval.end(); });
    return it != std::ranges::end(intervals) && it->start() <= time;
}

template<typename Intervals, typename Times, IsTimePoint Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>> && ForwardRangeOf<Times, Time>)
std::vector<Time> times_within(const Intervals& intervals, const Times& times) {
    std::vector<Time> within;
    std::ranges::copy_if(times, std::back_inserter(within),
            [&intervals](const Time time) { return contains(intervals, time); });
    return within;
}

template<typename Intervals, typename Times, IsTimePoint Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>> && ForwardRangeOf<Times, Time>)
std::vector<Time> times_within_sorted_disjoint(const Intervals& intervals, const Times& times) {
    std::vector<Time> within;
    std::ranges::copy_if(times, std::back_inserter(within),
            [&intervals](const Time time) { return contains_sorted_disjoint(intervals, time); });
    return within;
}

template<typename Intervals, IsTimePoint Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>>)
std::vector<TimeInterval<Time>> union_of(const Intervals& intervals) {
    std::vector<TimeInterval<Time>> sorted(std::ranges::begin(intervals), std::ranges::end(intervals));
    std::ranges::sort(sorted, std::less<>{}, [](const TimeInterval<Time>& interval) { return interval.start(); });
    // Merge each interval into the last merged interval if they overlap, otherwise start a new one
    std::vector<TimeInterval<Time>> merged;
    for (const TimeInterval<Time>& interval : sorted) {
        if (!merged.empty() && is_overlapping(merged.back(), interval)) {
            merged.back() = union_of(merged.back(), interval);
        } else {
            merged.push_back(interval);
        }
    }
    return merged;
}

template<typename LhsIntervals, typename RhsIntervals, IsTimePoint Time>
    requires(ForwardRangeOf<LhsIntervals, TimeInterval<Time>> && ForwardRangeOf<RhsIntervals, TimeInterval<Time>>)
std::vector<TimeInterval<Time>> intersection_of(const LhsIntervals& lhs, const RhsIntervals& rhs) {
    return intersection_of_sorted_disjoint(union_of(lhs), union_of(rhs));
}

template<typename LhsIntervals, typename RhsIntervals, IsTimePoint Time>
    requires(ForwardRangeOf<LhsIntervals, TimeInterval<Time>> && ForwardRangeOf<RhsIntervals, TimeInterval<Time>>)
std::vector<TimeInterval<Time>> intersection_of_sorted_disjoint(const LhsIntervals& lhs, const RhsIntervals& rhs) {
    std::vector<TimeInterval<Time>> intersection;
    auto lhs_it = std::ranges::begin(lhs);
    auto rhs_it = std::ranges::begin(rhs);
    while (lhs_it != std::ranges::end(lhs) && rhs_it != std::ranges::end(rhs)) {
        if (is_overlapping(*lhs_it, *rhs_it)) {
            intersection.push_back(intersection_of(*lhs_it, *rhs_it));
        }
        // The interval which ends first overlaps no later interval of the other set
        if (lhs_it->end() < rhs_it->end()) {
            ++lhs_it;
        } else {
            ++rhs_it;
        }
    }
    return intersection;
}

template<typename Intervals, IsTimePoint Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>>)
typename Time::duration span_of(const Intervals& intervals) {
    typename Time::duration span{Time::duration::zero()};
    for (const TimeInterval<Time>& interval : union_of(intervals)) {
        span += interval.span();
    }
    return span;
}

template<typename Intervals, IsTimePoint Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>>)
double coverage_of(const Intervals& intervals, const TimeInterval<Time>& interval) {
    throw_if(interval.span() == Time::duration::zero(),
            "Cannot get the coverage of an interval with a zero span.", std::invalid_argument);
    return to_sec(span_of(intersection_of(intervals, std::array{interval}))) / to_sec(interval.span());
}

}

#endif
