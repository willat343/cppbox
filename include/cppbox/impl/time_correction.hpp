#ifndef CPPBOX_IMPL_TIME_CORRECTION_HPP
#define CPPBOX_IMPL_TIME_CORRECTION_HPP

#include "cppbox/exceptions.hpp"
#include "cppbox/time_correction.hpp"

namespace cppbox {

template<IsTimePoint Time_>
inline TimeCorrection<Time_>::TimeCorrection() : TimeCorrection(1.0, Time()) {}

template<IsTimePoint Time_>
inline TimeCorrection<Time_>::TimeCorrection(const double rate_, const Time& origin_) : rate_(rate_), origin_(origin_) {
    throw_if(rate_ <= 0.0, "Time correction rate must be positive for corrected times to strictly increase.");
}

template<IsTimePoint Time_>
inline auto TimeCorrection<Time_>::apply(const Time time) const -> Time {
    // Equivalent to origin + rate (time - origin), but exact in time when the rate is 1
    return time + to_duration<Duration>((rate_ - 1.0) * to_sec(time - origin_));
}

template<IsTimePoint Time_>
inline double TimeCorrection<Time_>::rate() const {
    return rate_;
}

template<IsTimePoint Time_>
inline auto TimeCorrection<Time_>::origin() const -> const Time& {
    return origin_;
}

}

#endif
