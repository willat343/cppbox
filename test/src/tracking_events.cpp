#include "cppbox/tracking_events.hpp"

#include <gtest/gtest.h>

#include <chrono>

TEST(tracking_events, empty) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};
    EXPECT_TRUE(events.empty());

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));

    EXPECT_TRUE(events.empty_before(start));
    EXPECT_FALSE(events.empty_at_or_before(start));
    EXPECT_FALSE(events.empty_before(start + Duration(4)));
    EXPECT_FALSE(events.empty_after(start + Duration(4)));
    EXPECT_FALSE(events.empty_at_or_after(start + Duration(8)));
    EXPECT_TRUE(events.empty_after(start + Duration(8)));
}

TEST(tracking_events, previous_time) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(events.previous_time(start));
    EXPECT_ANY_THROW(events.previous_time_from_end(start));
    EXPECT_ANY_THROW(events.previous_time_from_start(start));

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));

    EXPECT_ANY_THROW(events.previous_time(start - Duration(1)));
    EXPECT_ANY_THROW(events.previous_time_from_end(start - Duration(1)));
    EXPECT_ANY_THROW(events.previous_time_from_start(start - Duration(1)));
    EXPECT_EQ(events.previous_time(start), start);
    EXPECT_EQ(events.previous_time_from_end(start), start);
    EXPECT_EQ(events.previous_time_from_start(start), start);
    EXPECT_EQ(events.previous_time(start + Duration(3)), start);
    EXPECT_EQ(events.previous_time_from_end(start + Duration(3)), start);
    EXPECT_EQ(events.previous_time_from_start(start + Duration(3)), start);
    EXPECT_EQ(events.previous_time(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.previous_time_from_end(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.previous_time_from_start(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.previous_time(start + Duration(8)), start + Duration(8));
    EXPECT_EQ(events.previous_time_from_end(start + Duration(8)), start + Duration(8));
    EXPECT_EQ(events.previous_time_from_start(start + Duration(8)), start + Duration(8));
    EXPECT_EQ(events.previous_time(start + Duration(9)), start + Duration(8));
    EXPECT_EQ(events.previous_time_from_end(start + Duration(9)), start + Duration(8));
    EXPECT_EQ(events.previous_time_from_start(start + Duration(9)), start + Duration(8));
}

TEST(tracking_events, next_time) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(events.next_time(start));
    EXPECT_ANY_THROW(events.next_time_from_end(start));
    EXPECT_ANY_THROW(events.next_time_from_start(start));

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));

    EXPECT_EQ(events.next_time(start - Duration(1)), start);
    EXPECT_EQ(events.next_time_from_end(start - Duration(1)), start);
    EXPECT_EQ(events.next_time_from_start(start - Duration(1)), start);
    EXPECT_EQ(events.next_time(start), start);
    EXPECT_EQ(events.next_time_from_end(start), start);
    EXPECT_EQ(events.next_time_from_start(start), start);
    EXPECT_EQ(events.next_time(start + Duration(3)), start + Duration(4));
    EXPECT_EQ(events.next_time_from_end(start + Duration(3)), start + Duration(4));
    EXPECT_EQ(events.next_time_from_start(start + Duration(3)), start + Duration(4));
    EXPECT_EQ(events.next_time(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.next_time_from_end(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.next_time_from_start(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.next_time(start + Duration(8)), start + Duration(8));
    EXPECT_EQ(events.next_time_from_end(start + Duration(8)), start + Duration(8));
    EXPECT_EQ(events.next_time_from_start(start + Duration(8)), start + Duration(8));
    EXPECT_ANY_THROW(events.next_time(start + Duration(9)));
    EXPECT_ANY_THROW(events.next_time_from_end(start + Duration(9)));
    EXPECT_ANY_THROW(events.next_time_from_start(start + Duration(9)));
}

TEST(tracking_events, duration) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(events.duration_since(start));
    EXPECT_ANY_THROW(events.duration_since_from_end(start));
    EXPECT_ANY_THROW(events.duration_since_from_start(start));

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));
    events.register_event(start + Duration(12));

    EXPECT_EQ(events.duration_since(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_since_from_end(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_since_from_start(start + Duration(6)), Duration(2));

    EXPECT_EQ(events.duration_until(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_until_from_end(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_until_from_start(start + Duration(6)), Duration(2));
}
