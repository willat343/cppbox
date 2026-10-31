#ifndef CPPBOX_TIME_INTERVALS_HPP
#define CPPBOX_TIME_INTERVALS_HPP

#include <ranges>
#include <vector>

#include "cppbox/ranges.hpp"
#include "cppbox/time.hpp"
#include "cppbox/time_interval.hpp"

namespace cppbox {

/**
 * @brief Check if any of a set of intervals contains `time`, in linear time.
 *
 * @tparam Time
 * @tparam Intervals
 * @param intervals intervals, in any order and possibly overlapping
 * @param time
 * @return true
 * @return false
 */
template<IsTimePoint Time, ForwardRangeOf<TimeInterval<Time>> Intervals>
bool contains(const Intervals& intervals, const Time time);

/**
 * @brief Check if any of a set of sorted and disjoint intervals contains `time`, in logarithmic time (for random
 * access ranges).
 *
 * @tparam Time
 * @tparam Intervals
 * @param intervals intervals, sorted and disjoint (e.g. from `union_of`)
 * @param time
 * @return true
 * @return false
 */
template<IsTimePoint Time, ForwardRangeOf<TimeInterval<Time>> Intervals>
bool contains_sorted_disjoint(const Intervals& intervals, const Time time);

/**
 * @brief Get the times contained by any of a set of intervals, in their original order, in linear time per time.
 *
 * @tparam Intervals
 * @tparam Times
 * @tparam Time time of the intervals, deduced from them
 * @param intervals intervals, in any order and possibly overlapping
 * @param times
 * @return std::vector<Time>
 */
template<typename Intervals, typename Times, IsTimePoint Time = typename std::ranges::range_value_t<Intervals>::Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>> && ForwardRangeOf<Times, Time>)
std::vector<Time> times_within(const Intervals& intervals, const Times& times);

/**
 * @brief Get the times contained by any of a set of sorted and disjoint intervals, in their original order, in
 * logarithmic time per time (for random access ranges).
 *
 * @tparam Intervals
 * @tparam Times
 * @tparam Time time of the intervals, deduced from them
 * @param intervals intervals, sorted and disjoint (e.g. from `union_of`)
 * @param times
 * @return std::vector<Time>
 */
template<typename Intervals, typename Times, IsTimePoint Time = typename std::ranges::range_value_t<Intervals>::Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>> && ForwardRangeOf<Times, Time>)
std::vector<Time> times_within_sorted_disjoint(const Intervals& intervals, const Times& times);

/**
 * @brief Get the union of a set of intervals, i.e. the sorted and disjoint intervals of the times within any of them,
 * where overlapping intervals (including those that share a bound) are merged.
 *
 * @tparam Intervals
 * @tparam Time time of the intervals, deduced from them
 * @param intervals intervals, in any order and possibly overlapping
 * @return std::vector<TimeInterval<Time>>
 */
template<typename Intervals, IsTimePoint Time = typename std::ranges::range_value_t<Intervals>::Time>
    requires(ForwardRangeOf<Intervals, TimeInterval<Time>>)
std::vector<TimeInterval<Time>> union_of(const Intervals& intervals);

/**
 * @brief Get the intersection of two sets of intervals, i.e. the sorted and disjoint intervals of the times within
 * both.
 *
 * @tparam LhsIntervals
 * @tparam RhsIntervals
 * @tparam Time time of the intervals, deduced from them
 * @param lhs intervals, in any order and possibly overlapping
 * @param rhs intervals, in any order and possibly overlapping
 * @return std::vector<TimeInterval<Time>>
 */
template<typename LhsIntervals, typename RhsIntervals,
        IsTimePoint Time = typename std::ranges::range_value_t<LhsIntervals>::Time>
    requires(ForwardRangeOf<LhsIntervals, TimeInterval<Time>> && ForwardRangeOf<RhsIntervals, TimeInterval<Time>>)
std::vector<TimeInterval<Time>> intersection_of(const LhsIntervals& lhs, const RhsIntervals& rhs);

/**
 * @brief Get the intersection of two sets of sorted and disjoint intervals, i.e. the sorted and disjoint intervals of
 * the times within both, in linear time.
 *
 * @tparam LhsIntervals
 * @tparam RhsIntervals
 * @tparam Time time of the intervals, deduced from them
 * @param lhs intervals, sorted and disjoint (e.g. from `union_of`)
 * @param rhs intervals, sorted and disjoint (e.g. from `union_of`)
 * @return std::vector<TimeInterval<Time>>
 */
template<typename LhsIntervals, typename RhsIntervals,
        IsTimePoint Time = typename std::ranges::range_value_t<LhsIntervals>::Time>
    requires(ForwardRangeOf<LhsIntervals, TimeInterval<Time>> && ForwardRangeOf<RhsIntervals, TimeInterval<Time>>)
std::vector<TimeInterval<Time>> intersection_of_sorted_disjoint(const LhsIntervals& lhs, const RhsIntervals& rhs);

}

#include "cppbox/impl/time_intervals.hpp"

#endif
