#include "cppbox/time_keeper.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <limits>
#include <string>

TEST(ordered_time_keeper, start_and_end_on_empty_throw) {
    using Time = std::chrono::steady_clock::time_point;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    EXPECT_ANY_THROW(time_keeper.start());
    EXPECT_ANY_THROW(time_keeper.end());
}

TEST(ordered_time_keeper, push_back_and_basic_queries) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    EXPECT_TRUE(time_keeper.empty());
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(2));
    time_keeper.push_back(start + Duration(4));
    EXPECT_FALSE(time_keeper.empty());
    EXPECT_EQ(time_keeper.size(), 3);
    EXPECT_EQ(time_keeper.start(), start);
    EXPECT_EQ(time_keeper.end(), start + Duration(4));
    EXPECT_EQ(time_keeper.time(1), start + Duration(2));
    EXPECT_ANY_THROW(time_keeper.push_back(start));
}

TEST(ordered_time_keeper, find_index_variants) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(2));
    time_keeper.push_back(start + Duration(4));
    EXPECT_EQ(time_keeper.find_index(start - Duration(1)), -1);
    EXPECT_EQ(time_keeper.find_index(start + Duration(1)), 0);
    EXPECT_EQ(time_keeper.find_index(start + Duration(4)), 2);
    EXPECT_EQ(time_keeper.find_index_from_end(start + Duration(1)), 0);
    EXPECT_EQ(time_keeper.find_index_from_start(start + Duration(1)), 0);
}

TEST(ordered_time_keeper, has_time_variants) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(2));
    EXPECT_TRUE(time_keeper.has_time(start));
    EXPECT_FALSE(time_keeper.has_time(start + Duration(1)));
    EXPECT_TRUE(time_keeper.has_time_at(0, start));
    EXPECT_FALSE(time_keeper.has_time_at(0, start + Duration(2)));
    EXPECT_TRUE(time_keeper.has_time_within(start + Duration(1)));
    EXPECT_FALSE(time_keeper.has_time_within(start - Duration(1)));
}

TEST(ordered_time_keeper, intervals) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(2));
    time_keeper.push_back(start + Duration(5));
    EXPECT_EQ(time_keeper.interval(0), Duration(2));
    EXPECT_EQ(time_keeper.interval_front(), Duration(2));
    EXPECT_EQ(time_keeper.interval_back(), Duration(3));
}

TEST(ordered_time_keeper, require_time_and_require_time_within) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(4));
    time_keeper.require_time(start + Duration(6));
    EXPECT_EQ(time_keeper.size(), 3);
    time_keeper.require_time(start + Duration(6));
    EXPECT_EQ(time_keeper.size(), 3);
    EXPECT_ANY_THROW(time_keeper.require_time(start + Duration(2)));

    cppbox::OrderedTimeKeeper<Time> time_keeper2;
    time_keeper2.push_back(start);
    time_keeper2.require_time_within(start + Duration(1));
    EXPECT_EQ(time_keeper2.size(), 2);
}

TEST(ordered_time_keeper, change_start_and_end_time) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    time_keeper.push_back(start + Duration(2));
    time_keeper.push_back(start + Duration(4));
    time_keeper.change_start_time(start - Duration(1));
    EXPECT_EQ(time_keeper.start(), start - Duration(1));
    EXPECT_ANY_THROW(time_keeper.change_start_time(start + Duration(3)));
    time_keeper.change_end_time(start + Duration(10));
    EXPECT_EQ(time_keeper.end(), start + Duration(10));
    EXPECT_ANY_THROW(time_keeper.change_end_time(start + Duration(1)));
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

TEST(ordered_time_keeper, queriable_and_reset) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::OrderedTimeKeeper<Time> time_keeper;
    Time start{Duration(0)};
    time_keeper.push_back(start);
    EXPECT_TRUE(time_keeper.queriable(0));
    EXPECT_FALSE(time_keeper.queriable(1));
    EXPECT_FALSE(time_keeper.queriable(-1));
    time_keeper.reset();
    EXPECT_TRUE(time_keeper.empty());
}

TEST(uniform_time_keeper, defaults_and_construction) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    const cppbox::UniformTimeKeeper<Time> default_time_keeper;
    EXPECT_EQ(default_time_keeper.start(), Time());
    EXPECT_ANY_THROW(cppbox::UniformTimeKeeper<Time>(Time(), Duration::zero()));
}

TEST(uniform_time_keeper, time_and_interval) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::UniformTimeKeeper<Time> time_keeper(start, Duration(2));
    EXPECT_EQ(time_keeper.time(0), start);
    EXPECT_EQ(time_keeper.time(3), start + Duration(6));
    EXPECT_EQ(time_keeper.interval(), Duration(2));
    EXPECT_EQ(time_keeper.interval(0), Duration(2));
    EXPECT_EQ(time_keeper.end(), Time::max());
    EXPECT_EQ(time_keeper.size(), std::numeric_limits<int>::max());
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

TEST(uniform_time_keeper, push_back_throws) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::UniformTimeKeeper<Time> time_keeper(Time{Duration(0)}, Duration(1));
    EXPECT_ANY_THROW(time_keeper.push_back(Time{Duration(0)}));
}

TEST(uniform_time_keeper, queriable_and_reset_are_trivial) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::UniformTimeKeeper<Time> time_keeper(Time{Duration(0)}, Duration(1));
    EXPECT_TRUE(time_keeper.queriable(-100));
    EXPECT_TRUE(time_keeper.queriable(100));
    time_keeper.reset();
}

TEST(uniform_time_keeper, require_time_and_require_time_within) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    cppbox::UniformTimeKeeper<Time> time_keeper(start, Duration(2));
    time_keeper.require_time(start + Duration(2));
    EXPECT_ANY_THROW(time_keeper.require_time(start + Duration(1)));
    time_keeper.require_time_within(start + Duration(1));
    EXPECT_ANY_THROW(time_keeper.require_time_within(start - Duration(1)));
}

TEST(uniform_time_keeper, change_start_time) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::UniformTimeKeeper<Time> time_keeper(Time{Duration(0)}, Duration(1));
    time_keeper.change_start_time(Time{Duration(5)});
    EXPECT_EQ(time_keeper.start(), Time{Duration(5)});
}
