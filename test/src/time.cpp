#include "cppbox/time.hpp"

#include <gtest/gtest.h>

#include <chrono>

TEST(time, to_string_duration_sign) {
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(0)), "0.000000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(500)), "0.500000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(-500)), "-0.500000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(1500)), "1.500000000");
    EXPECT_EQ(cppbox::to_string(std::chrono::milliseconds(-1500)), "-1.500000000");
}
