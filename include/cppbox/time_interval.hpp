#ifndef CPPBOX_TIME_INTERVAL_HPP
#define CPPBOX_TIME_INTERVAL_HPP

#include <ostream>
#include <string>

#include "cppbox/time.hpp"

namespace cppbox {

template<IsTimePoint Time_>
class TimeInterval {
public:
    using Time = Time_;
    using Duration = Time::duration;

    explicit TimeInterval();

    explicit TimeInterval(const Time& start_, const Time& end_);

    /**
     * @brief Check if the closed interval \f$[start, end]\f$ contains `time`.
     *
     * @param time
     * @return true
     * @return false
     */
    bool contains(const Time time) const;

    /**
     * @brief Check if the closed interval \f$[start, end]\f$ contains all of `interval`.
     *
     * @param interval
     * @return true
     * @return false
     */
    bool contains(const TimeInterval interval) const;

    /**
     * @brief Check if the open interval \f$(start, end)\f$ contains `time`, excluding both bounds.
     *
     * @param time
     * @return true
     * @return false
     */
    bool contains_open(const Time time) const;

    /**
     * @brief Check if the left-open interval \f$(start, end]\f$ contains `time`, excluding the start bound.
     *
     * @param time
     * @return true
     * @return false
     */
    bool contains_left_open(const Time time) const;

    /**
     * @brief Check if the right-open interval \f$[start, end)\f$ contains `time`, excluding the end bound.
     *
     * @param time
     * @return true
     * @return false
     */
    bool contains_right_open(const Time time) const;

    const Time& end() const;

    Time& end();

    Duration span() const;

    const Time& start() const;

    Time& start();

    std::string to_string() const;

    bool within(const TimeInterval interval) const;

    bool operator==(const TimeInterval&) const = default;

private:
    Time start_;
    Time end_;
};

template<IsTimePoint Time_>
std::ostream& operator<<(std::ostream& os, const TimeInterval<Time_>& interval);

template<IsTimePoint Time>
TimeInterval<Time> intersection_of(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs);

template<IsTimePoint Time>
bool is_overlapping(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs);

template<IsTimePoint Time>
TimeInterval<Time> union_of(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs);

}

#include "cppbox/impl/time_interval.hpp"

#endif
