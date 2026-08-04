#include "cppbox/time_keeper.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <string>

TEST(ordered_time_keeper, start_and_end_on_empty_throw) {
    using Time = std::chrono::steady_clock::time_point;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    EXPECT_ANY_THROW(time_keeper.start());
    EXPECT_ANY_THROW(time_keeper.end());
}

TEST(ordered_time_keeper, change_time_index_equal_to_size_throws_bounds_message) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(1));
    try {
        time_keeper.change_time(time_keeper.size(), start);
        FAIL() << "Expected change_time to throw for index == size()";
    } catch (const std::exception& e) {
        EXPECT_NE(std::string(e.what()).find("out of bounds"), std::string::npos);
    }
}

TEST(uniform_time_keeper, find_index_exact_multiple_before_start) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    cppbox::UniformTimeKeeper<Time> time_keeper(start, Duration(2));
    EXPECT_EQ(time_keeper.find_index(start), 0);
    EXPECT_EQ(time_keeper.find_index(start - Duration(1)), -1);
    EXPECT_EQ(time_keeper.find_index(start - Duration(2)), -1);
    EXPECT_EQ(time_keeper.find_index(start - Duration(3)), -2);
    EXPECT_EQ(time_keeper.find_index(start - Duration(4)), -2);
}
