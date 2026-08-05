#include "cppbox/time.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>
#include <vector>

TEST(time, to_string_duration_sign) {
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(0)), "0.000000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(500)), "0.500000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(-500)), "-0.500000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(1500)), "1.500000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(-1500)), "-1.500000000");
}

TEST(time, to_string_time_point) {
    using Time = std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;
    const Time time{std::chrono::nanoseconds(1500000000)};
    EXPECT_EQ(cppbox::to_string(time), "1.500000000");
}

TEST(time, to_duration) {
    EXPECT_EQ(cppbox::to_duration<int>(5.0), 5);
    EXPECT_EQ(cppbox::to_duration<std::chrono::milliseconds>(1.5), std::chrono::milliseconds(1500));
}

TEST(time, to_nsec) {
    EXPECT_EQ(cppbox::to_nsec(std::chrono::milliseconds(1)), 1000000);
    EXPECT_EQ((cppbox::to_nsec<std::int64_t>(2.0)), 2);
    using Time = std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;
    const Time time{std::chrono::nanoseconds(500)};
    EXPECT_EQ(cppbox::to_nsec(time), 500);
}

TEST(time, to_sec) {
    EXPECT_EQ(cppbox::to_sec(std::chrono::milliseconds(1500)), 1.5);
    EXPECT_EQ(cppbox::to_sec(2.5), 2.5);
}

TEST(time, to_secs) {
    const std::vector<std::chrono::milliseconds> durations{std::chrono::milliseconds(500),
            std::chrono::milliseconds(1000)};
    const std::vector<double> expected{0.5, 1.0};
    EXPECT_EQ(cppbox::to_secs(durations), expected);
}

TEST(time, to_time) {
    using Time = std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;
    const Time time = cppbox::to_time<Time>(1.5);
    EXPECT_EQ(time.time_since_epoch(), std::chrono::nanoseconds(1500000000));
    EXPECT_EQ(cppbox::to_time<double>(2.5), 2.5);
}

TEST(time, type_traits) {
    EXPECT_TRUE(cppbox::is_duration_v<std::chrono::milliseconds>);
    EXPECT_FALSE(cppbox::is_duration_v<int>);
    EXPECT_TRUE(cppbox::is_time_point_v<std::chrono::steady_clock::time_point>);
    EXPECT_FALSE(cppbox::is_time_point_v<int>);
    EXPECT_TRUE(cppbox::is_time_point_or_duration_v<std::chrono::milliseconds>);
    EXPECT_TRUE(cppbox::is_time_point_or_duration_v<std::chrono::steady_clock::time_point>);
    EXPECT_FALSE(cppbox::is_time_point_or_duration_v<int>);
}
