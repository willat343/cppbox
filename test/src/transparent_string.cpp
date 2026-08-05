#include "cppbox/transparent_string.hpp"

#include <gtest/gtest.h>

TEST(transparent_string, unordered_map_heterogeneous_lookup) {
    cppbox::TransparentStringUnorderedMap<int> map;
    map.emplace("hello", 1);
    map.emplace("world", 2);
    EXPECT_EQ(map.at("hello"), 1);
    EXPECT_EQ(map.find(std::string_view("world"))->second, 2);
    EXPECT_TRUE(map.contains("hello"));
    EXPECT_FALSE(map.contains("missing"));
}

TEST(transparent_string, unordered_set_heterogeneous_lookup) {
    cppbox::TransparentStringUnorderedSet set;
    set.insert("hello");
    set.insert("world");
    EXPECT_TRUE(set.contains(std::string_view("hello")));
    EXPECT_FALSE(set.contains("missing"));
}
