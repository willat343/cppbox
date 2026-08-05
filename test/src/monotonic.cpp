#include "cppbox/monotonic.hpp"

#include <gtest/gtest.h>

TEST(monotonic_increasing, construct_with_value) {
    cppbox::MonotonicIncreasing<int> monotonic(5);
    EXPECT_EQ(monotonic.value(), 5);
}

TEST(monotonic_increasing, update) {
    cppbox::MonotonicIncreasing<int> monotonic(5);
    monotonic.update(5);
    EXPECT_EQ(monotonic.value(), 5);
    monotonic.update(7);
    EXPECT_EQ(monotonic.value(), 7);
    EXPECT_ANY_THROW(monotonic.update(6));
    EXPECT_EQ(monotonic.value(), 7);
}

TEST(monotonic_increasing, try_update) {
    cppbox::MonotonicIncreasing<int> monotonic(5);
    monotonic.try_update(3);
    EXPECT_EQ(monotonic.value(), 5);
    monotonic.try_update(5);
    EXPECT_EQ(monotonic.value(), 5);
    monotonic.try_update(9);
    EXPECT_EQ(monotonic.value(), 9);
}
