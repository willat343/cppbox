#ifndef CPPBOX_TIME_CORRECTION_HPP
#define CPPBOX_TIME_CORRECTION_HPP

#include "cppbox/time.hpp"

namespace cppbox {

/**
 * @brief Linear correction of times from a clock running at a constant rate relative to a reference clock.
 *
 * A time \f$ t \f$ is corrected to \f$ t_0 + r (t - t_0) \f$, where the rate \f$ r \f$ is the rate of the reference
 * clock relative to the corrected clock (s/s, 1 for no drift) and the origin \f$ t_0 \f$ is the time at which both
 * clocks agree. The correction is strictly increasing, which requires \f$ r > 0 \f$.
 */
template<IsTimePoint Time_>
class TimeCorrection {
public:
    using Time = Time_;
    using Duration = Time::duration;

    explicit TimeCorrection(const double rate_, const Time& origin_);

    /**
     * @brief Correct a time.
     *
     * @param time
     * @return Time
     */
    Time apply(const Time time) const;

    double rate() const;

    const Time& origin() const;

private:
    double rate_;
    Time origin_;
};

}

#include "cppbox/impl/time_correction.hpp"

#endif
