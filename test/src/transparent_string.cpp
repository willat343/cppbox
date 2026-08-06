#include "cppbox/transparent_string.hpp"

#include <gtest/gtest.h>

// Heterogeneous (string_view) lookup on unordered containers is a libstdc++ >= 11 feature; this project's dev build
// targets g++-10, so these tests exercise the map/set with std::string keys rather than string_view/const char*.
TEST(transparent_string, unordered_map_lookup) {
    cppbox::TransparentStringUnorderedMap<int> map;
    map.emplace("hello", 1);
    map.emplace("world", 2);
    EXPECT_EQ(map.at("hello"), 1);
    EXPECT_EQ(map.find(std::string("world"))->second, 2);
    EXPECT_TRUE(map.contains("hello"));
    EXPECT_FALSE(map.contains("missing"));
}

TEST(transparent_string, unordered_set_lookup) {
    cppbox::TransparentStringUnorderedSet set;
    set.insert("hello");
    set.insert("world");
    EXPECT_TRUE(set.contains("hello"));
    EXPECT_FALSE(set.contains("missing"));
}
