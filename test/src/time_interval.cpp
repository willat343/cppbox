#include "cppbox/time_interval.hpp"

#include <gtest/gtest.h>

#include <chrono>

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
