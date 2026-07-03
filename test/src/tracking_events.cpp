#include "cppbox/tracking_events.hpp"

#include <gtest/gtest.h>

#include <chrono>

TEST(tracking_events, previous_and_next_times) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};
    EXPECT_TRUE(events.empty());
    EXPECT_ANY_THROW(events.previous_time(start));
    EXPECT_ANY_THROW(events.next_time(start));

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));

    EXPECT_EQ(events.previous_time(start + Duration(3)), start);
    EXPECT_EQ(events.previous_time(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.previous_time(start + Duration(9)), start + Duration(8));
    EXPECT_EQ(events.next_time(start + Duration(3)), start + Duration(4));
    EXPECT_EQ(events.next_time(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.next_time(start + Duration(8)), start + Duration(8));
    EXPECT_ANY_THROW(events.next_time(start + Duration(9)));
}
