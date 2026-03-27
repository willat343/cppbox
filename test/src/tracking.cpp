#include "cppbox/tracking.hpp"

#include <gtest/gtest.h>

#include <chrono>

TEST(binary_tracking, updates) {
    using Time = std::chrono::steady_clock::time_point;
    cppbox::BinaryTracking<Time> tracking;
    Time start{Time::duration(0)};
    EXPECT_ANY_THROW(tracking.at(start));
    EXPECT_ANY_THROW(tracking.at_time(start));
    EXPECT_ANY_THROW(tracking.last());
    EXPECT_ANY_THROW(tracking.last_time());
    EXPECT_ANY_THROW(tracking.equal_since_time());
    EXPECT_FALSE(tracking.has_tracking_at(start));
    auto update_and_check = [&tracking](const Time time, const bool element) {
        tracking.update(time, element);
        EXPECT_EQ(tracking.at(time), element);
        Time at_time;
        EXPECT_EQ(tracking.at(time, at_time), element);
        EXPECT_EQ(at_time, time);
        EXPECT_EQ(tracking.at_time(time), time);
        EXPECT_EQ(tracking.last(), element);
        EXPECT_EQ(tracking.last_time(), time);
        EXPECT_TRUE(tracking.has_tracking_at(time));
        EXPECT_TRUE(tracking.has_tracking_at(time + Time::duration(1)));
    };
    update_and_check(start, true);
    EXPECT_EQ(tracking.equal_since_time(), start);
    update_and_check(start + Time::duration(1), true);
    EXPECT_EQ(tracking.equal_since_time(), start);
    update_and_check(start + Time::duration(2), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(2));
    update_and_check(start + Time::duration(3), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(2));
    update_and_check(start + Time::duration(4), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(2));
    update_and_check(start + Time::duration(5), true);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(5));
    update_and_check(start + Time::duration(6), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(6));
    update_and_check(start + Time::duration(7), true);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(7));
    update_and_check(start + Time::duration(9), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Time::duration(9));
    EXPECT_EQ(tracking.at(start + Time::duration(8)), true);
    EXPECT_EQ(tracking.at(start + Time::duration(9)), false);
    EXPECT_FALSE(tracking.has_tracking_at(start - Time::duration(1)));
}

TEST(binary_multi_tracking, updates) {
    using Time = std::chrono::steady_clock::time_point;
    cppbox::BinaryMultiTracking<Time> multi_tracking;
    Time start{Time::duration(0)};
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    multi_tracking.update(start, {{"a", true}, {"b", false}});
    EXPECT_TRUE(multi_tracking.has_tracking("a"));
    EXPECT_TRUE(multi_tracking.has_tracking("b"));
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_TRUE(multi_tracking.is_synchronised_to(start));
    EXPECT_EQ(multi_tracking.synchronisation_time(), start);
    multi_tracking.update(start + Time::duration(1), "a", false);
    EXPECT_FALSE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start + Time::duration(1)));
    EXPECT_ANY_THROW(multi_tracking.synchronisation_time());
    multi_tracking.update(start + Time::duration(1), "b", false);
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    EXPECT_TRUE(multi_tracking.is_synchronised_to(start + Time::duration(1)));
    EXPECT_EQ(multi_tracking.synchronisation_time(), start + Time::duration(1));
    multi_tracking.update(start + Time::duration(2), {{"a", true}, {"b", false}});
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start + Time::duration(1)));
    EXPECT_TRUE(multi_tracking.is_synchronised_to(start + Time::duration(2)));
    EXPECT_EQ(multi_tracking.synchronisation_time(), start + Time::duration(2));
}
