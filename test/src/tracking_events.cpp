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

    EXPECT_TRUE(events.empty_before(start));
    EXPECT_FALSE(events.empty_before(start + Duration(4)));
    EXPECT_FALSE(events.empty_after(start + Duration(4)));
    EXPECT_TRUE(events.empty_after(start + Duration(8)));

    EXPECT_EQ(events.previous_time(start + Duration(3)), start);
    EXPECT_EQ(events.previous_time(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.previous_time(start + Duration(9)), start + Duration(8));
    EXPECT_EQ(events.next_time(start + Duration(3)), start + Duration(4));
    EXPECT_EQ(events.next_time(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.next_time(start + Duration(8)), start + Duration(8));
    EXPECT_ANY_THROW(events.next_time(start + Duration(9)));
}

TEST(tracking_events, search_from_end) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));
    events.register_event(start + Duration(12));

    // All queries near the end should return correct results
    EXPECT_EQ(events.previous_time_from_end(start + Duration(10)), start + Duration(8));
    EXPECT_EQ(events.previous_time_from_end(start + Duration(12)), start + Duration(12));
    EXPECT_EQ(events.previous_time_from_end(start + Duration(20)), start + Duration(12));
    EXPECT_EQ(events.previous_time_from_end(start + Duration(1)), start);
}

TEST(tracking_events, search_from_start) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));
    events.register_event(start + Duration(12));

    // All queries should return correct results when searching from start
    EXPECT_EQ(events.previous_time_from_start(start + Duration(1)), start);
    EXPECT_EQ(events.previous_time_from_start(start + Duration(4)), start + Duration(4));
    EXPECT_EQ(events.previous_time_from_start(start + Duration(6)), start + Duration(4));
    EXPECT_EQ(events.previous_time_from_start(start + Duration(20)), start + Duration(12));

    EXPECT_EQ(events.next_time_from_start(start + Duration(0)), start);
    EXPECT_EQ(events.next_time_from_start(start + Duration(3)), start + Duration(4));
    EXPECT_EQ(events.next_time_from_start(start + Duration(5)), start + Duration(8));
    EXPECT_EQ(events.next_time_from_start(start + Duration(12)), start + Duration(12));
}

TEST(tracking_events, next_time_from_end) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));
    events.register_event(start + Duration(12));

    // All queries near the end should return correct results
    EXPECT_EQ(events.next_time_from_end(start + Duration(0)), start);
    EXPECT_EQ(events.next_time_from_end(start + Duration(5)), start + Duration(8));
    EXPECT_EQ(events.next_time_from_end(start + Duration(12)), start + Duration(12));
    EXPECT_EQ(events.next_time_from_end(start + Duration(9)), start + Duration(12));
}

TEST(tracking_events, duration_variants) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::TrackingEvents<Time> events;
    Time start{Duration(0)};

    events.register_event(start);
    events.register_event(start + Duration(4));
    events.register_event(start + Duration(8));
    events.register_event(start + Duration(12));

    // Test duration_since variants
    EXPECT_EQ(events.duration_since(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_since_from_end(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_since_from_start(start + Duration(6)), Duration(2));

    // Test duration_until variants
    EXPECT_EQ(events.duration_until(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_until_from_end(start + Duration(6)), Duration(2));
    EXPECT_EQ(events.duration_until_from_start(start + Duration(6)), Duration(2));
}
