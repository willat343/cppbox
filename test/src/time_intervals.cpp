#include "cppbox/time_intervals.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <vector>

TEST(time_intervals, contains) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Unsorted and overlapping
    const std::vector<Interval> intervals{Interval(Time{Duration(10)}, Time{Duration(12)}),
            Interval(Time{Duration(0)}, Time{Duration(4)}), Interval(Time{Duration(3)}, Time{Duration(6)})};
    EXPECT_TRUE(cppbox::contains(intervals, Time{Duration(5)}));
    EXPECT_TRUE(cppbox::contains(intervals, Time{Duration(12)}));
    EXPECT_FALSE(cppbox::contains(intervals, Time{Duration(8)}));
    EXPECT_FALSE(cppbox::contains(std::vector<Interval>{}, Time{Duration(0)}));
}

TEST(time_intervals, contains_sorted_disjoint) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Includes an interval of a single time
    const std::vector<Interval> intervals{Interval(Time{Duration(0)}, Time{Duration(4)}),
            Interval(Time{Duration(6)}, Time{Duration(6)}), Interval(Time{Duration(10)}, Time{Duration(12)})};
    for (int t = -1; t <= 13; ++t) {
        EXPECT_EQ(cppbox::contains_sorted_disjoint(intervals, Time{Duration(t)}),
                cppbox::contains(intervals, Time{Duration(t)}))
                << "t = " << t;
    }
    EXPECT_TRUE(cppbox::contains_sorted_disjoint(intervals, Time{Duration(6)}));
    EXPECT_FALSE(cppbox::contains_sorted_disjoint(intervals, Time{Duration(5)}));
    EXPECT_FALSE(cppbox::contains_sorted_disjoint(std::vector<Interval>{}, Time{Duration(0)}));
}

TEST(time_intervals, times_within) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Unsorted and overlapping
    const std::vector<Interval> intervals{Interval(Time{Duration(10)}, Time{Duration(12)}),
            Interval(Time{Duration(0)}, Time{Duration(4)}), Interval(Time{Duration(3)}, Time{Duration(6)})};
    const std::vector<Time> times{Time{Duration(11)}, Time{Duration(-1)}, Time{Duration(0)}, Time{Duration(8)},
            Time{Duration(6)}};
    EXPECT_EQ(cppbox::times_within(intervals, times),
            (std::vector<Time>{Time{Duration(11)}, Time{Duration(0)}, Time{Duration(6)}}));
    EXPECT_TRUE(cppbox::times_within(std::vector<Interval>{}, times).empty());
}

TEST(time_intervals, times_within_sorted_disjoint) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    const std::vector<Interval> intervals{Interval(Time{Duration(0)}, Time{Duration(4)}),
            Interval(Time{Duration(6)}, Time{Duration(6)}), Interval(Time{Duration(10)}, Time{Duration(12)})};
    std::vector<Time> times;
    for (int t = 13; t >= -1; --t) {
        times.emplace_back(Duration(t));
    }
    EXPECT_EQ(cppbox::times_within_sorted_disjoint(intervals, times), cppbox::times_within(intervals, times));
    EXPECT_EQ(cppbox::times_within_sorted_disjoint(intervals, times).size(), 9);
}

TEST(time_intervals, union_of) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Unsorted, overlapping, and sharing a bound
    const std::vector<Interval> intervals{Interval(Time{Duration(10)}, Time{Duration(12)}),
            Interval(Time{Duration(3)}, Time{Duration(6)}), Interval(Time{Duration(0)}, Time{Duration(4)}),
            Interval(Time{Duration(6)}, Time{Duration(7)}), Interval(Time{Duration(9)}, Time{Duration(9)})};
    EXPECT_EQ(cppbox::union_of(intervals),
            (std::vector<Interval>{Interval(Time{Duration(0)}, Time{Duration(7)}),
                    Interval(Time{Duration(9)}, Time{Duration(9)}), Interval(Time{Duration(10)}, Time{Duration(12)})}));
    EXPECT_TRUE(cppbox::union_of(std::vector<Interval>{}).empty());
}

TEST(time_intervals, intersection_of) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    const std::vector<Interval> lhs{Interval(Time{Duration(0)}, Time{Duration(4)}),
            Interval(Time{Duration(6)}, Time{Duration(10)})};
    const std::vector<Interval> rhs{Interval(Time{Duration(2)}, Time{Duration(7)}),
            Interval(Time{Duration(8)}, Time{Duration(8)}), Interval(Time{Duration(10)}, Time{Duration(20)})};
    const std::vector<Interval> expected{Interval(Time{Duration(2)}, Time{Duration(4)}),
            Interval(Time{Duration(6)}, Time{Duration(7)}), Interval(Time{Duration(8)}, Time{Duration(8)}),
            Interval(Time{Duration(10)}, Time{Duration(10)})};
    EXPECT_EQ(cppbox::intersection_of_sorted_disjoint(lhs, rhs), expected);
    EXPECT_EQ(cppbox::intersection_of_sorted_disjoint(rhs, lhs), expected);
    // Unsorted and overlapping inputs are merged first
    const std::vector<Interval> rhs_unsorted{Interval(Time{Duration(10)}, Time{Duration(20)}),
            Interval(Time{Duration(2)}, Time{Duration(5)}), Interval(Time{Duration(8)}, Time{Duration(8)}),
            Interval(Time{Duration(4)}, Time{Duration(7)})};
    EXPECT_EQ(cppbox::intersection_of(lhs, rhs_unsorted), expected);
    // An unbounded interval leaves the other set unchanged
    EXPECT_EQ(cppbox::intersection_of_sorted_disjoint(lhs, std::vector<Interval>{Interval()}), lhs);
    EXPECT_TRUE(cppbox::intersection_of_sorted_disjoint(lhs, std::vector<Interval>{}).empty());
}

TEST(time_intervals, span_of) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Unsorted and overlapping: the union is [0, 6] and [10, 12]
    const std::vector<Interval> intervals{Interval(Time{Duration(10)}, Time{Duration(12)}),
            Interval(Time{Duration(0)}, Time{Duration(4)}), Interval(Time{Duration(3)}, Time{Duration(6)})};
    EXPECT_EQ(cppbox::span_of(intervals), Duration(8));
    EXPECT_EQ(cppbox::span_of(std::vector<Interval>{}), Duration(0));
}

TEST(time_intervals, coverage_of) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Unsorted and overlapping: within [2, 12], the union [0, 6] and [10, 12] covers [2, 6] and [10, 12]
    const std::vector<Interval> intervals{Interval(Time{Duration(10)}, Time{Duration(12)}),
            Interval(Time{Duration(0)}, Time{Duration(4)}), Interval(Time{Duration(3)}, Time{Duration(6)})};
    EXPECT_DOUBLE_EQ(cppbox::coverage_of(intervals, Interval(Time{Duration(2)}, Time{Duration(12)})), 0.6);
    EXPECT_DOUBLE_EQ(cppbox::coverage_of(intervals, Interval(Time{Duration(7)}, Time{Duration(9)})), 0.0);
    EXPECT_DOUBLE_EQ(cppbox::coverage_of(std::vector<Interval>{}, Interval(Time{Duration(0)}, Time{Duration(1)})), 0.0);
    EXPECT_THROW(cppbox::coverage_of(intervals, Interval(Time{Duration(1)}, Time{Duration(1)})), std::invalid_argument);
}

TEST(time_intervals, complement_of) {
    using Time = std::chrono::steady_clock::time_point;
    using Duration = Time::duration;
    using Interval = cppbox::TimeInterval<Time>;
    // Unsorted and overlapping: within [2, 14], the union [0, 6] and [10, 12] leaves [6, 10] and [12, 14]
    const std::vector<Interval> intervals{Interval(Time{Duration(10)}, Time{Duration(12)}),
            Interval(Time{Duration(0)}, Time{Duration(4)}), Interval(Time{Duration(3)}, Time{Duration(6)})};
    EXPECT_EQ(cppbox::complement_of(intervals, Interval(Time{Duration(2)}, Time{Duration(14)})),
            (std::vector<Interval>{Interval(Time{Duration(6)}, Time{Duration(10)}),
                    Interval(Time{Duration(12)}, Time{Duration(14)})}));
    // Gap at the start, and none at the end as the interval ends where an interval ends
    EXPECT_EQ(cppbox::complement_of(intervals, Interval(Time{Duration(8)}, Time{Duration(12)})),
            (std::vector<Interval>{Interval(Time{Duration(8)}, Time{Duration(10)})}));
    EXPECT_TRUE(cppbox::complement_of(intervals, Interval(Time{Duration(1)}, Time{Duration(5)})).empty());
    EXPECT_EQ(cppbox::complement_of(std::vector<Interval>{}, Interval(Time{Duration(0)}, Time{Duration(1)})),
            (std::vector<Interval>{Interval(Time{Duration(0)}, Time{Duration(1)})}));
}
