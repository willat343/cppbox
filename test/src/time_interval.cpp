#include "cppbox/time_interval.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <sstream>

TEST(time_interval, default_constructor) {
    using Time = std::chrono::steady_clock::time_point;
    const cppbox::TimeInterval<Time> interval;
    EXPECT_EQ(interval.start(), Time());
    EXPECT_EQ(interval.end(), Time::max());
}

TEST(time_interval, invalid_bounds_throw) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(5)};
    EXPECT_ANY_THROW(cppbox::TimeInterval<Time>(start, start - Duration(1)));
}

TEST(time_interval, contains_time) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> interval(start, start + Duration(4));
    EXPECT_TRUE(interval.contains(start));
    EXPECT_TRUE(interval.contains(start + Duration(2)));
    EXPECT_TRUE(interval.contains(start + Duration(4)));
    EXPECT_FALSE(interval.contains(start - Duration(1)));
    EXPECT_FALSE(interval.contains(start + Duration(5)));
}

TEST(time_interval, contains_time_open) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> interval(start, start + Duration(4));
    EXPECT_FALSE(interval.contains_open(start));
    EXPECT_TRUE(interval.contains_open(start + Duration(2)));
    EXPECT_FALSE(interval.contains_open(start + Duration(4)));
    EXPECT_FALSE(interval.contains_open(start - Duration(1)));
    EXPECT_FALSE(interval.contains_open(start + Duration(5)));
}

TEST(time_interval, contains_time_left_open) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> interval(start, start + Duration(4));
    EXPECT_FALSE(interval.contains_left_open(start));
    EXPECT_TRUE(interval.contains_left_open(start + Duration(2)));
    EXPECT_TRUE(interval.contains_left_open(start + Duration(4)));
    EXPECT_FALSE(interval.contains_left_open(start - Duration(1)));
    EXPECT_FALSE(interval.contains_left_open(start + Duration(5)));
}

TEST(time_interval, contains_time_right_open) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> interval(start, start + Duration(4));
    EXPECT_TRUE(interval.contains_right_open(start));
    EXPECT_TRUE(interval.contains_right_open(start + Duration(2)));
    EXPECT_FALSE(interval.contains_right_open(start + Duration(4)));
    EXPECT_FALSE(interval.contains_right_open(start - Duration(1)));
    EXPECT_FALSE(interval.contains_right_open(start + Duration(5)));
}

TEST(time_interval, adjacent_intervals_share_bound_exactly_once) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> first(start, start + Duration(4));
    const cppbox::TimeInterval<Time> second(start + Duration(4), start + Duration(8));
    const Time shared = start + Duration(4);
    EXPECT_TRUE(first.contains(shared) && second.contains(shared));
    EXPECT_NE(first.contains_right_open(shared), second.contains_right_open(shared));
    EXPECT_NE(first.contains_left_open(shared), second.contains_left_open(shared));
}

TEST(time_interval, empty_interval) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(3)};
    const cppbox::TimeInterval<Time> interval(start, start);
    EXPECT_TRUE(interval.contains(start));
    EXPECT_FALSE(interval.contains_open(start));
    EXPECT_FALSE(interval.contains_left_open(start));
    EXPECT_FALSE(interval.contains_right_open(start));
}

TEST(time_interval, contains_and_within_interval) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> outer(start, start + Duration(10));
    const cppbox::TimeInterval<Time> inner(start + Duration(2), start + Duration(4));
    EXPECT_TRUE(outer.contains(inner));
    EXPECT_TRUE(inner.within(outer));
    EXPECT_FALSE(inner.contains(outer));
    EXPECT_FALSE(outer.within(inner));
}

TEST(time_interval, span) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> interval(start, start + Duration(4));
    EXPECT_EQ(interval.span(), Duration(4));
}

TEST(time_interval, mutable_accessors) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    cppbox::TimeInterval<Time> interval(start, start + Duration(4));
    interval.start() = start + Duration(1);
    interval.end() = start + Duration(5);
    EXPECT_EQ(interval.start(), start + Duration(1));
    EXPECT_EQ(interval.end(), start + Duration(5));
}

TEST(time_interval, to_string_and_stream) {
    using Time = std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;
    const Time start{std::chrono::nanoseconds(0)};
    const cppbox::TimeInterval<Time> interval(start, start + std::chrono::seconds(1));
    EXPECT_EQ(interval.to_string(), "[0.000000000, 1.000000000]");
    std::ostringstream ss;
    ss << interval;
    EXPECT_EQ(ss.str(), interval.to_string());
}

TEST(time_interval, equality) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> a(start, start + Duration(4));
    const cppbox::TimeInterval<Time> b(start, start + Duration(4));
    const cppbox::TimeInterval<Time> c(start, start + Duration(5));
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(time_interval, is_overlapping) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> a(start, start + Duration(2));
    const cppbox::TimeInterval<Time> b(start + Duration(1), start + Duration(3));
    const cppbox::TimeInterval<Time> c(start + Duration(5), start + Duration(6));
    EXPECT_TRUE(cppbox::is_overlapping(a, b));
    EXPECT_TRUE(cppbox::is_overlapping(b, a));
    EXPECT_FALSE(cppbox::is_overlapping(a, c));
    EXPECT_FALSE(cppbox::is_overlapping(c, a));
}

TEST(time_interval, intersection_and_union_require_overlap) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    Time start{Duration(0)};
    const cppbox::TimeInterval<Time> a(start, start + Duration(2));
    const cppbox::TimeInterval<Time> b(start + Duration(1), start + Duration(3));
    const cppbox::TimeInterval<Time> c(start + Duration(5), start + Duration(6));
    EXPECT_EQ(cppbox::intersection_of(a, b), cppbox::TimeInterval<Time>(start + Duration(1), start + Duration(2)));
    EXPECT_EQ(cppbox::union_of(a, b), cppbox::TimeInterval<Time>(start, start + Duration(3)));
    EXPECT_ANY_THROW(cppbox::intersection_of(a, c));
    EXPECT_ANY_THROW(cppbox::union_of(a, c));
}
