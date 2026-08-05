#include "cppbox/constexpr_hash.hpp"

#include <gtest/gtest.h>

enum class ConstexprHashTestColour { RED, GREEN, BLUE };

TEST(constexpr_hash, fnv1a_deterministic_and_distinct) {
    EXPECT_EQ(cppbox::fnv1a_32("hello"), cppbox::fnv1a_32("hello"));
    EXPECT_NE(cppbox::fnv1a_32("hello"), cppbox::fnv1a_32("world"));
    EXPECT_EQ(cppbox::fnv1a_64("hello"), cppbox::fnv1a_64("hello"));
    EXPECT_NE(cppbox::fnv1a_64("hello"), cppbox::fnv1a_64("world"));
}

TEST(constexpr_hash, integral) {
    constexpr cppbox::ConstexprHash<int> hash;
    EXPECT_EQ(hash(5), hash(5));
    EXPECT_NE(hash(5), hash(-5));
}

TEST(constexpr_hash, enum_type) {
    constexpr cppbox::ConstexprHash<ConstexprHashTestColour> hash;
    EXPECT_EQ(hash(ConstexprHashTestColour::RED), hash(ConstexprHashTestColour::RED));
    EXPECT_NE(hash(ConstexprHashTestColour::RED), hash(ConstexprHashTestColour::GREEN));
}

TEST(constexpr_hash, string_view) {
    constexpr cppbox::ConstexprHash<std::string_view> hash;
    EXPECT_EQ(hash("hello"), hash(std::string_view("hello")));
    EXPECT_NE(hash("hello"), hash("world"));
}

TEST(constexpr_hash, const_char_pointer_matches_string_view) {
    constexpr cppbox::ConstexprHash<const char*> char_hash;
    constexpr cppbox::ConstexprHash<std::string_view> view_hash;
    EXPECT_EQ(char_hash("hello"), view_hash("hello"));
}
