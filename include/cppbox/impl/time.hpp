#ifndef CPPBOX_IMPL_TIME_HPP
#define CPPBOX_IMPL_TIME_HPP

#include <iomanip>
#include <sstream>

#include "cppbox/time.hpp"

namespace cppbox {

template<class Duration, typename Scalar>
    requires(std::is_arithmetic_v<Duration> || is_duration_v<Duration>)
constexpr inline Duration to_duration(const Scalar seconds) {
    if constexpr (std::is_arithmetic_v<Duration>) {
        return static_cast<Duration>(seconds);
    } else if constexpr (is_duration_v<Duration>) {
        return std::chrono::duration_cast<Duration>(std::chrono::duration<Scalar>(seconds));
    }
}

template<typename Scalar, class TimeOrDuration>
    requires(std::is_arithmetic_v<TimeOrDuration> || is_time_point_or_duration_v<TimeOrDuration>)
constexpr inline Scalar to_sec(const TimeOrDuration& time_or_duration) {
    if constexpr (std::is_arithmetic_v<TimeOrDuration>) {
        return static_cast<Scalar>(time_or_duration);
    } else if constexpr (is_time_point_v<TimeOrDuration>) {
        return to_sec<Scalar, typename TimeOrDuration::duration>(time_or_duration.time_since_epoch());
    } else if constexpr (is_duration_v<TimeOrDuration>) {
        return std::chrono::duration<Scalar>(time_or_duration).count();
    }
}

template<typename Scalar, class TimeOrDuration>
    requires(std::is_arithmetic_v<TimeOrDuration> || is_time_point_or_duration_v<TimeOrDuration>)
std::vector<Scalar> to_secs(const std::vector<TimeOrDuration>& times_or_durations) {
    std::vector<Scalar> seconds(times_or_durations.size());
    std::transform(times_or_durations.cbegin(), times_or_durations.cend(), seconds.begin(),
            to_sec<Scalar, TimeOrDuration>);
    return seconds;
}

template<IsTimePointOrDuration TimeOrDuration>
std::string to_string(const TimeOrDuration& time_or_duration) {
    if constexpr (is_time_point_v<TimeOrDuration>) {
        return to_string(time_or_duration.time_since_epoch());
    } else if constexpr (is_duration_v<TimeOrDuration>) {
        std::stringstream ss;
        ss << time_or_duration / std::chrono::seconds(1) << "." << std::setw(9) << std::setfill('0')
           << std::abs((time_or_duration % std::chrono::seconds(1)) / std::chrono::nanoseconds(1));
        return ss.str();
    }
}

template<class Time, typename Scalar>
    requires(std::is_arithmetic_v<Time> || is_time_point_v<Time>)
constexpr inline Time to_time(const Scalar seconds) {
    if constexpr (std::is_arithmetic_v<Time>) {
        return static_cast<Time>(seconds);
    } else if constexpr (is_time_point_v<Time>) {
        return Time(to_duration<typename Time::duration>(seconds));
    }
}

}

#endif
