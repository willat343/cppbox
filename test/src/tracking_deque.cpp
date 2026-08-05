#include "cppbox/tracking_deque.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

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

TEST(tracking_deque, basic_deque_operations) {
    cppbox::TrackingDeque<int> deque;
    EXPECT_TRUE(deque.empty());
    deque.push_back(1);
    deque.push_back(2);
    deque.push_front(0);
    EXPECT_EQ(deque.size(), 3u);
    EXPECT_EQ(deque.front(), 0);
    EXPECT_EQ(deque.back(), 2);
    EXPECT_EQ(deque.at(1), 1);
    EXPECT_EQ(deque[1], 1);
    const std::vector<int> collected(deque.begin(), deque.end());
    EXPECT_EQ(collected, (std::vector<int>{0, 1, 2}));
    deque.pop_front();
    deque.pop_back();
    EXPECT_EQ(deque.size(), 1u);
    EXPECT_EQ(deque.front(), 1);
    deque.clear();
    EXPECT_TRUE(deque.empty());
}

TEST(tracking_deque, pop_on_empty_throws) {
    cppbox::TrackingDeque<int> deque;
    EXPECT_ANY_THROW(deque.pop_back());
    EXPECT_ANY_THROW(deque.pop_front());
}

TEST(tracking_deque, emplace_back_and_erase) {
    cppbox::TrackingDeque<std::string> deque;
    deque.emplace_back("a");
    deque.emplace_back("b");
    EXPECT_EQ(deque.count("a"), 1u);
    const auto it = deque.erase(deque.begin());
    EXPECT_EQ(*it, "b");
    EXPECT_EQ(deque.count("a"), 0u);
}

TEST(tracking_deque, track_and_untrack) {
    cppbox::TrackingDeque<int> deque;
    deque.track(1);
    EXPECT_FALSE(deque.has_any_tracked());
    EXPECT_FALSE(deque.has_all_tracked());
    deque.push_back(1);
    EXPECT_TRUE(deque.has_any_tracked());
    EXPECT_TRUE(deque.has_all_tracked());
    deque.track(2);
    EXPECT_TRUE(deque.has_any_tracked());
    EXPECT_FALSE(deque.has_all_tracked());
    deque.push_back(2);
    EXPECT_TRUE(deque.has_all_tracked());
    deque.untrack(1);
    EXPECT_TRUE(deque.has_all_tracked());
}
