#include "cppbox/array.hpp"

#include <gtest/gtest.h>

TEST(array, contains) {
    const std::array<int, 4> values{1, 2, 3, 4};
    EXPECT_TRUE(cppbox::contains(values, 3));
    EXPECT_FALSE(cppbox::contains(values, 5));
}

TEST(array, merge) {
    const std::array<int, 2> a{1, 2};
    const std::array<int, 3> b{3, 4, 5};
    const std::array<int, 5> merged = cppbox::merge(a, b);
    const std::array<int, 5> expected{1, 2, 3, 4, 5};
    EXPECT_EQ(merged, expected);
}
