#include "cppbox/constexpr_map.hpp"

#include <gtest/gtest.h>

TEST(constexpr_map, stringview_to_size) {
    constexpr auto sizes =
            cppbox::ConstexprMap(std::to_array<cppbox::ConstexprMapEntry<std::string_view, std::size_t>>({
                    {"bool", sizeof(bool)},
                    {"int32", sizeof(int32_t)},
                    {"float64", sizeof(double)},
            }));
    EXPECT_TRUE(sizes.find("bool").has_value());
    EXPECT_TRUE(sizes.find("int32").has_value());
    EXPECT_TRUE(sizes.find("float64").has_value());
    EXPECT_EQ(sizes.find("bool").value_or(0), sizeof(bool));
    EXPECT_EQ(sizes.find("int32").value_or(0), sizeof(int32_t));
    EXPECT_EQ(sizes.find("float64").value_or(0), sizeof(double));
    EXPECT_EQ(sizes.get_or("bool", 0), sizeof(bool));
    EXPECT_EQ(sizes.get_or("int32", 0), sizeof(int32_t));
    EXPECT_EQ(sizes.get_or("float64", 0), sizeof(double));
    EXPECT_FALSE(sizes.find("missing").has_value());
    const std::size_t missing_value = 1234;
    EXPECT_EQ(sizes.get_or("missing", missing_value), missing_value);
}
