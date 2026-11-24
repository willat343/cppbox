#include "cppbox/ranges.hpp"

#include <gtest/gtest.h>

#include <array>
#include <chrono>
#include <list>
#include <vector>

TEST(ranges, is_strictly_decreasing) {
    EXPECT_TRUE(cppbox::is_strictly_decreasing(std::vector<int>{}));
    EXPECT_TRUE(cppbox::is_strictly_decreasing(std::vector<int>{1}));
    EXPECT_TRUE(cppbox::is_strictly_decreasing(std::vector<int>{3, 2, 1}));
    EXPECT_FALSE(cppbox::is_strictly_decreasing(std::vector<int>{3, 2, 2}));
    EXPECT_FALSE(cppbox::is_strictly_decreasing(std::vector<int>{3, 1, 2}));
    EXPECT_FALSE(cppbox::is_strictly_decreasing(std::vector<int>{1, 2, 3}));
    // A forward range that is not random access
    EXPECT_TRUE(cppbox::is_strictly_decreasing(std::list<double>{0.3, 0.2, -0.1}));
    static_assert(cppbox::is_strictly_decreasing(std::array<int, 3>{3, 2, 1}));
}

TEST(ranges, is_strictly_increasing) {
    EXPECT_TRUE(cppbox::is_strictly_increasing(std::vector<int>{}));
    EXPECT_TRUE(cppbox::is_strictly_increasing(std::vector<int>{1}));
    EXPECT_TRUE(cppbox::is_strictly_increasing(std::vector<int>{1, 2, 3}));
    EXPECT_FALSE(cppbox::is_strictly_increasing(std::vector<int>{1, 2, 2}));
    EXPECT_FALSE(cppbox::is_strictly_increasing(std::vector<int>{1, 3, 2}));
    EXPECT_FALSE(cppbox::is_strictly_increasing(std::vector<int>{3, 2, 1}));
    // A forward range that is not random access
    EXPECT_TRUE(cppbox::is_strictly_increasing(std::list<double>{-0.1, 0.2, 0.3}));
    // Time points
    const std::chrono::steady_clock::time_point start;
    const std::chrono::milliseconds step(1);
    EXPECT_TRUE(cppbox::is_strictly_increasing(std::vector{start, start + step, start + 2 * step}));
    EXPECT_FALSE(cppbox::is_strictly_increasing(std::vector{start, start, start + step}));
    static_assert(cppbox::is_strictly_increasing(std::array<int, 3>{1, 2, 3}));
}
