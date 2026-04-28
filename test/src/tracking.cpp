#include "cppbox/tracking.hpp"

#include <gtest/gtest.h>

#include <chrono>

template<typename Element, cppbox::IsTimePoint Time>
void update_and_check(cppbox::Tracking<Element, Time>& tracking, const Time time, const Element& element) {
    using Duration = Time::duration;
    tracking.update(time, element);
    EXPECT_EQ(tracking.at(time), element);
    Time at_time;
    EXPECT_EQ(tracking.at(time, at_time), element);
    EXPECT_EQ(at_time, time);
    EXPECT_EQ(tracking.at_time(time), time);
    EXPECT_EQ(tracking.last(), element);
    EXPECT_EQ(tracking.last_time(), time);
    EXPECT_TRUE(tracking.has_tracking_at(time));
    EXPECT_TRUE(tracking.has_tracking_at(time + Duration(1)));
}

TEST(binary_tracking, updates) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::BinaryTracking<Time> tracking;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(tracking.at(start));
    EXPECT_ANY_THROW(tracking.at_time(start));
    EXPECT_ANY_THROW(tracking.last());
    EXPECT_ANY_THROW(tracking.last_time());
    EXPECT_ANY_THROW(tracking.equal_since_time());
    EXPECT_FALSE(tracking.has_tracking_at(start));
    update_and_check(tracking, start, true);
    EXPECT_EQ(tracking.equal_since_time(), start);
    update_and_check(tracking, start + Duration(1), true);
    EXPECT_EQ(tracking.equal_since_time(), start);
    update_and_check(tracking, start + Duration(2), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(2));
    update_and_check(tracking, start + Duration(3), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(2));
    update_and_check(tracking, start + Duration(4), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(2));
    update_and_check(tracking, start + Duration(5), true);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(5));
    update_and_check(tracking, start + Duration(6), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(6));
    update_and_check(tracking, start + Duration(7), true);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(7));
    update_and_check(tracking, start + Duration(9), false);
    EXPECT_EQ(tracking.equal_since_time(), start + Duration(9));
    EXPECT_EQ(tracking.at(start + Duration(8)), true);
    EXPECT_EQ(tracking.at(start + Duration(9)), false);
    EXPECT_FALSE(tracking.has_tracking_at(start - Duration(1)));
    EXPECT_EQ(tracking.at_time_interval(start), cppbox::TimeInterval<Time>(start, start + Duration(1)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(1)), cppbox::TimeInterval<Time>(start, start + Duration(1)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(2)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(3)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(4)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(5)),
            cppbox::TimeInterval<Time>(start + Duration(5), start + Duration(5)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(6)),
            cppbox::TimeInterval<Time>(start + Duration(6), start + Duration(6)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(7)),
            cppbox::TimeInterval<Time>(start + Duration(7), start + Duration(7)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(8)),
            cppbox::TimeInterval<Time>(start + Duration(7), start + Duration(7)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(9)),
            cppbox::TimeInterval<Time>(start + Duration(9), start + Duration(9)));
}

TEST(binary_tracking, triple_update_time_interval_permutation_0) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::BinaryTracking<Time> tracking;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(tracking.at_time_interval(start));
    update_and_check(tracking, start, true);
    update_and_check(tracking, start + Duration(2), true);
    update_and_check(tracking, start + Duration(4), true);
    EXPECT_EQ(tracking.at_time_interval(start), cppbox::TimeInterval<Time>(start, start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(1)), cppbox::TimeInterval<Time>(start, start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(2)), cppbox::TimeInterval<Time>(start, start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(3)), cppbox::TimeInterval<Time>(start, start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(4)), cppbox::TimeInterval<Time>(start, start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(5)), cppbox::TimeInterval<Time>(start, start + Duration(4)));
}

TEST(binary_tracking, triple_update_time_interval_permutation_1) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::BinaryTracking<Time> tracking;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(tracking.at_time_interval(start));
    update_and_check(tracking, start, true);
    update_and_check(tracking, start + Duration(2), true);
    update_and_check(tracking, start + Duration(4), false);
    EXPECT_EQ(tracking.at_time_interval(start), cppbox::TimeInterval<Time>(start, start + Duration(2)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(1)), cppbox::TimeInterval<Time>(start, start + Duration(2)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(2)), cppbox::TimeInterval<Time>(start, start + Duration(2)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(3)), cppbox::TimeInterval<Time>(start, start + Duration(2)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(4)),
            cppbox::TimeInterval<Time>(start + Duration(4), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(5)),
            cppbox::TimeInterval<Time>(start + Duration(4), start + Duration(4)));
}

TEST(binary_tracking, triple_update_time_interval_permutation_2) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::BinaryTracking<Time> tracking;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(tracking.at_time_interval(start));
    update_and_check(tracking, start, true);
    update_and_check(tracking, start + Duration(2), false);
    update_and_check(tracking, start + Duration(4), true);
    EXPECT_EQ(tracking.at_time_interval(start), cppbox::TimeInterval<Time>(start, start));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(1)), cppbox::TimeInterval<Time>(start, start));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(2)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(2)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(3)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(2)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(4)),
            cppbox::TimeInterval<Time>(start + Duration(4), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(5)),
            cppbox::TimeInterval<Time>(start + Duration(4), start + Duration(4)));
}

TEST(binary_tracking, triple_update_time_interval_permutation_3) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::BinaryTracking<Time> tracking;
    Time start{Duration(0)};
    EXPECT_ANY_THROW(tracking.at_time_interval(start));
    update_and_check(tracking, start, false);
    update_and_check(tracking, start + Duration(2), true);
    update_and_check(tracking, start + Duration(4), true);
    EXPECT_EQ(tracking.at_time_interval(start), cppbox::TimeInterval<Time>(start, start));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(1)), cppbox::TimeInterval<Time>(start, start));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(2)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(3)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(4)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
    EXPECT_EQ(tracking.at_time_interval(start + Duration(5)),
            cppbox::TimeInterval<Time>(start + Duration(2), start + Duration(4)));
}

TEST(binary_multi_tracking, updates) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    cppbox::BinaryMultiTracking<Time> multi_tracking;
    Time start{Duration(0)};
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    multi_tracking.update(start, {{"a", true}, {"b", false}});
    EXPECT_TRUE(multi_tracking.has_tracking("a"));
    EXPECT_TRUE(multi_tracking.has_tracking("b"));
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_TRUE(multi_tracking.is_synchronised_to(start));
    EXPECT_EQ(multi_tracking.synchronisation_time(), start);
    multi_tracking.update(start + Duration(1), "a", false);
    EXPECT_FALSE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start + Duration(1)));
    EXPECT_ANY_THROW(multi_tracking.synchronisation_time());
    multi_tracking.update(start + Duration(1), "b", false);
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    EXPECT_TRUE(multi_tracking.is_synchronised_to(start + Duration(1)));
    EXPECT_EQ(multi_tracking.synchronisation_time(), start + Duration(1));
    multi_tracking.update(start + Duration(2), {{"a", true}, {"b", false}});
    EXPECT_TRUE(multi_tracking.is_synchronised());
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start));
    EXPECT_FALSE(multi_tracking.is_synchronised_to(start + Duration(1)));
    EXPECT_TRUE(multi_tracking.is_synchronised_to(start + Duration(2)));
    EXPECT_EQ(multi_tracking.synchronisation_time(), start + Duration(2));
}
