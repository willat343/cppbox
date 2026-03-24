#ifndef CPPBOX_TIME_INTERVAL_HPP
#define CPPBOX_TIME_INTERVAL_HPP

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

    const Time& end() const;

    Time& end();

    Duration span() const;

    const Time& start() const;

    Time& start();

    std::string to_string() const;

private:
    Time start_;
    Time end_;
};

template<IsTimePoint Time>
TimeInterval<Time> intersection_of(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs);

template<IsTimePoint Time>
bool is_overlapping(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs);

template<IsTimePoint Time>
TimeInterval<Time> union_of(const TimeInterval<Time>& lhs, const TimeInterval<Time>& rhs);

}

#include "cppbox/impl/time_interval.hpp"

#endif
