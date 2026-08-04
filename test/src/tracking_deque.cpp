#include "cppbox/tracking_deque.hpp"

#include <gtest/gtest.h>

TEST(tracking_deque, count_tracked) {
    cppbox::TrackingDeque<int> deque;
    deque.track(1);
    deque.track(2);
    deque.push_back(1);
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    EXPECT_EQ(deque.count(1), 2u);
    EXPECT_EQ(deque.count(2), 1u);
    EXPECT_EQ(deque.count(3), 1u);
    EXPECT_EQ(deque.count_tracked(), 3u);
}
