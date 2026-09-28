#include "cppbox/time_correction.hpp"

#include <gtest/gtest.h>

#include <chrono>

using Time = std::chrono::steady_clock::time_point;

TEST(time_correction, unit_rate_is_identity) {
    const cppbox::TimeCorrection<Time> correction(1.0, Time{std::chrono::seconds(1000)});
    const Time time{std::chrono::nanoseconds(1234567890123)};
    EXPECT_EQ(correction.apply(time), time);
}

TEST(time_correction, zero_at_origin) {
    const Time origin{std::chrono::seconds(1000)};
    const cppbox::TimeCorrection<Time> correction(1.0 - 2.5e-5, origin);
    EXPECT_EQ(correction.apply(origin), origin);
}

TEST(time_correction, linear_about_origin) {
    // A clock running fast by 25 ppm is corrected back by 2.5 ms per 100 s after the origin, and forward before it
    const Time origin{std::chrono::seconds(1000)};
    const cppbox::TimeCorrection<Time> correction(1.0 - 2.5e-5, origin);
    EXPECT_EQ(correction.apply(origin + std::chrono::seconds(100)),
            origin + std::chrono::seconds(100) - std::chrono::microseconds(2500));
    EXPECT_EQ(correction.apply(origin - std::chrono::seconds(100)),
            origin - std::chrono::seconds(100) + std::chrono::microseconds(2500));
}

TEST(time_correction, strictly_increasing) {
    const cppbox::TimeCorrection<Time> correction(0.5, Time{std::chrono::seconds(10)});
    Time previous = correction.apply(Time{});
    for (int i = 1; i <= 100; ++i) {
        const Time corrected = correction.apply(Time{std::chrono::milliseconds(200 * i)});
        EXPECT_GT(corrected, previous);
        previous = corrected;
    }
}

TEST(time_correction, non_positive_rate_throws) {
    EXPECT_ANY_THROW(cppbox::TimeCorrection<Time>(0.0, Time{}));
    EXPECT_ANY_THROW(cppbox::TimeCorrection<Time>(-1.0, Time{}));
}
