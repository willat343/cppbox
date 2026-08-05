#include "cppbox/temporal_vector.hpp"

#include <gtest/gtest.h>

#include <chrono>

TEST(ordered_temporal_vector, emplace_back_and_access) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTemporalVector<int, Time> vector;
    Time start{Duration(0)};
    EXPECT_TRUE(vector.empty());
    vector.emplace_back(start, 1);
    vector.emplace_back(start + Duration(1), 2);
    vector.emplace_back(start + Duration(2), 3);
    EXPECT_EQ(vector.size(), 3u);
    EXPECT_EQ(vector.element(0), 1);
    EXPECT_EQ(vector.element_front(), 1);
    EXPECT_EQ(vector.element_back(), 3);
    EXPECT_EQ(vector.start_time(), start);
    EXPECT_EQ(vector.end_time(), start + Duration(2));
    EXPECT_EQ(vector.time(1), start + Duration(1));
}

TEST(ordered_temporal_vector, change_time_and_reset) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTemporalVector<int, Time> vector;
    Time start{Duration(0)};
    vector.emplace_back(start, 1);
    vector.emplace_back(start + Duration(1), 2);
    vector.change_end_time(start + Duration(5));
    EXPECT_EQ(vector.end_time(), start + Duration(5));
    vector.change_time(0, start - Duration(1));
    EXPECT_EQ(vector.time(0), start - Duration(1));
    vector.reset();
    EXPECT_TRUE(vector.empty());
}

TEST(uniform_temporal_vector, emplace_back_at_uniform_times) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    cppbox::UniformTemporalVector<int, Time> vector(start, Duration(1));
    vector.emplace_back(1);
    vector.emplace_back(2);
    EXPECT_EQ(vector.size(), 2u);
    EXPECT_EQ(vector.time(0), start);
    EXPECT_EQ(vector.time(1), start + Duration(1));
}
